#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>

class Memory
{
private:
	DWORD pID = 0;
	HANDLE pHandle = NULL;
public:
	Memory(const char* processName);
	~Memory();

	DWORD getPID();
	HANDLE getProcessHandle();

	uintptr_t GetBase(const char* moduleName);

	bool isProcessOpen();

	template <typename T>
	T Read(uintptr_t address) {
		T value;
		ReadProcessMemory(pHandle, (LPCVOID)address, &value, sizeof(T), 0);
		return value;
	}

	template <typename T>
	bool Write(uintptr_t address, T value) {
		return WriteProcessMemory(pHandle, (LPCVOID)address, &value, sizeof(T), 0);
	}
};

