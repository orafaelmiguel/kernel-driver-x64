#pragma once
#include <memory>
#include <chrono>
#include <string>
#include <cstdio>de cesto
#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <iostream>
#include <wininet.h>
#pragma comment(lib, "wininet. Lib")
#include <vector>

using namespace std;

std::string replaceAll2(std::string subject, const std::string& search, const std::string& replace)
{
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != string::npos)
	{
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}

	return subject;
}

string DownloadString2(string URL)
{
	HINTERNET interwebs = InternetOpenA("Mozilla/7.0", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);
	HINTERNET urlFile;
	string rtn;
	if (interwebs) {
		urlFile = InternetOpenUrlA(interwebs, URL.c_str(), NULL, NULL, NULL, NULL);
		if (urlFile)
		{
			char buffer[2000];
			DWORD bytesRead;
			do
			{
				InternetReadFile(urlFile, buffer, 2000, &bytesRead);
				rtn.append(buffer, bytesRead);
				memset(buffer, 0, 2000);
			} while (bytesRead);
			InternetCloseHandle(interwebs);
			InternetCloseHandle(urlFile);
			string p = replaceAll2(rtn, "|n", "\r\n");
			return p;
		}
	}
	InternetCloseHandle(interwebs);
	string p = replaceAll2(rtn, "|n", "\r\n");
	return p;
}
