### Kernel Mode Driver - Memory Read/Write 

This project is a Windows kernel mode driver designed to enable reading and writing to the memory of a specified process. It is commonly used in scenarios such as game cheats where memory access to another process is required. However, note that using this driver to cheat in games or for any malicious purpose can result in bans and legal consequences. Use it for educational purposes only.

🚧 This repository is under development 🚧

### Features 
  - Attach to a target process by its PID (Process ID).
  - Read memory from the target process.
  - Write memory to the target process.
  - Communication between user mode and kernel mode via IOCTL calls.
  - Basic debugging capabilities via kernel debug prints.

### Requirements 

  - *Windows Development Kit (WDK)*: Required to build and develop Windows drivers.
  - *Visual Studio*: Preferred IDE for driver development. Make sure to install the WDK components.
  - *Proper System Configuration*: Ensure your system is configured to allow unsigned drivers (for testing) or sign your driver with a valid certificate.

### Driver Design

  This driver is composed of several important components:

  - *Driver Entry*: The starting point of the driver, where it is initialized and its major functions (e.g., device control) are set up.
  - *IOCTL Interface*: Allows communication between user mode applications and the kernel driver.
  - *Memory Management Functions*: Enable copying of memory between the target process and the calling process using MmCopyVirtualMemory.
  - *Device Creation and Symbolic Links*: The driver creates a device and a symbolic link that can be accessed from user mode.

### Usage

  Compilation
  
  1 - Install the Windows Driver Kit (WDK): You will need this to compile kernel mode drivers.
  2 - Build the Driver: Use Visual Studio with WDK installed to compile the driver in x64 Release or Debug mode.

### Installation

  1 - Test Mode: If you're testing and your driver is unsigned, you will need to enable Test Mode on Windows:
  ```
    bcdedit /set testsigning on
  ```
