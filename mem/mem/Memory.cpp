#include "Memory.h"

Memory::Memory(const char* processName) {
	const auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(snapshot, &pe)) {
		while (Process32Next(snapshot, &pe)) {
			if (strcmp(pe.szExeFile, processName) == 0) {
				pID = pe.th32ProcessID;
				pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
				if (pHandle) {
					std::cout << "Attached Successfully!\n";
				}
			}
		}
	}
	CloseHandle(snapshot);
}

Memory::~Memory() {
	CloseHandle(pHandle);
}

DWORD Memory::getPID() {
	return pID;
}

HANDLE Memory::getProcessHandle() {
	return pHandle;
}

uintptr_t Memory::GetBase(const char* moduleName) {
	uintptr_t base;

	const auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pID);

	MODULEENTRY32 me;
	me.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(snapshot, &me)) {
		while (Module32Next(snapshot, &me)) {
			if (strcmp(me.szModule, moduleName) == 0) {
				base = reinterpret_cast<uintptr_t>(me.modBaseAddr);
			}
		}
	}
	CloseHandle(snapshot);
	return base;
}

bool Memory::isProcessOpen() {
	DWORD pID = this->pID;
	if (pID == 0) {
		std::cout << "Process is Closed!\n";
		exit(1);
		return false;
	}
	else {
		std::cout << "Process is Opened!\n";
	}
}