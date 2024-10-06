#include <ntifs.h>

extern "C"
{
	NTKERNELAPI NTSTATUS IoCreateDriver(PUNICODE_STRING DriverName, PDRIVER_INITIALIZE InitializationFunction);

	NTKERNELAPI NTSTATUS MmCopyVirtualMemory(PEPROCESS SourceProcess, PVOID SourceAddress, PEPROCESS TargetProcess, PVOID TargetAddress, SIZE_T BufferSize, KPROCESSOR_MODE PreviousMode, PSIZE_T ReturnSize);
}

void debug_print(PCSTR text)
{
#ifndef DEBUG
	UNREFERENCED_PARAMETER(text);
#endif
	KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, text));
}

namespace driver
{
	namespace codes
	{
		constexpr ULONG attach =
			// Setup Driver
			CTL_CODE(FILE_DEVICE_UNKNOWN, 0x696, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);

		constexpr ULONG read =
			// Read process memory
			CTL_CODE(FILE_DEVICE_UNKNOWN, 0x697, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);

		constexpr ULONG write =
			//Read process memory
			CTL_CODE(FILE_DEVICE_UNKNOWN, 0x698, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
	}

	// user mode <> kernel mode
	struct Request
	{
		HANDLE process_id;

		PVOID target;
		PVOID buffer;

		SIZE_T size;
		SIZE_T return_size;
	};

	NTSTATUS create(PDEVICE_OBJECT device_object, PIRP irp)
	{
		UNREFERENCED_PARAMETER(device_object);

		IoCompleteRequest(irp, IO_NO_INCREMENT);

		return irp->IoStatus.Status;
	}

	NTSTATUS close(PDEVICE_OBJECT device_object, PIRP irp)
	{
		UNREFERENCED_PARAMETER(device_object);

		IoCompleteRequest(irp, IO_NO_INCREMENT);

		return irp->IoStatus.Status;
	}

	NTSTATUS device_control(PDEVICE_OBJECT device_object, PIRP irp)
	{
		UNREFERENCED_PARAMETER(device_object);

		debug_print("Device control called");

		NTSTATUS status = STATUS_UNSUCCESSFUL;

		PIO_STACK_LOCATION stack_irp = IoGetCurrentIrpStackLocation(irp);

		auto request = reinterpret_cast<Request*>(irp->AssociatedIrp.SystemBuffer);

		if (stack_irp == nullptr || request == nullptr)
		{
			IoCompleteRequest(irp, IO_NO_INCREMENT);
			return status;
		}

		static PEPROCESS target_process = nullptr;

		const ULONG control_code = stack_irp->Parameters.DeviceIoControl.IoControlCode;
		switch (control_code)
		{
			case codes::attach:
				status = PsLookupProcessByProcessId(request->process_id, &target_process);
				break;

			case codes::read:
				if (target_process != nullptr)
				{
					status = MmCopyVirtualMemory(target_process, request->target, PsGetCurrentProcess(), request->buffer, request->size, KernelMode, &request->return_size);
				}
				break;

			case codes::write:
				if (target_process != nullptr)
				{
					status = MmCopyVirtualMemory(PsGetCurrentProcess(), request->buffer, target_process, request->target, request->size, KernelMode, &request->return_size);
				}
				break;

			default:
				break;
		}

		irp->IoStatus.Status = status;
		irp->IoStatus.Information = sizeof(Request);

		IoCompleteRequest(irp, IO_NO_INCREMENT);

		return status;
	}
}

// Real entrypoint
NTSTATUS driver_main(PDRIVER_OBJECT driver_object, PUNICODE_STRING registry_path)
{
	UNREFERENCED_PARAMETER(registry_path);

	UNICODE_STRING device_name = {};
	RtlInitUnicodeString(&device_name, L"\\Device\\kernel-driver-x64");
	
	// driver device obj.
	PDEVICE_OBJECT device_object = nullptr;
	NTSTATUS status = IoCreateDevice(driver_object, 0, &device_name, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &device_object);

	if (status != STATUS_SUCCESS)
	{
		debug_print("[-] Faile to create driver device.");
		return status;
	}

	debug_print("Driver device successfully created.");

	UNICODE_STRING symbolic_link = {};
	RtlInitUnicodeString(&device_name, L"\\DosDevice\\kernel-driver-x64");

	status = IoCreateSymbolicLink(&symbolic_link, &device_name);
	if (status != STATUS_SUCCESS)
	{
		debug_print("[-] Faile to estabilish symbolic link.");
		return status;
	}

	debug_print("Driver symbolic link successfully estabilished.");

	SetFlag(device_object->Flags, DO_BUFFERED_IO);

	driver_object->MajorFunction[IRP_MJ_CREATE] = driver::create;
	driver_object->MajorFunction[IRP_MJ_CLOSE] = driver::close;
	driver_object->MajorFunction[IRP_MJ_DEVICE_CONTROL] = driver::device_control;

	ClearFlag(device_object->Flags, DO_DEVICE_INITIALIZING);

	return STATUS_SUCCESS;
}

NTSTATUS DriverEntry()
{
	debug_print("Variant on Kernel");

	UNICODE_STRING driver_name = {};
	RtlInitUnicodeString(&driver_name, L"\\Driver\\kernel-driver-x64");

	return IoCreateDriver(&driver_name, &driver_main);
}

