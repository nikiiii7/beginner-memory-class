#include <iostream>
#include "mem/Memory.h"
#include "Offsets.cpp"

int main() {
	auto mem = Memory("cs2.exe");

	if (!mem.isProcessOpen()) {
		mem.isProcessOpen();
	}

	uintptr_t base = mem.GetBase("client.dll");
	uintptr_t localPlayer = mem.Read<uintptr_t>(base + offsets::dwLocalPlayerPawn);

	while (true) {
		int health = mem.Read<int>(localPlayer + offsets::m_iHealth);

		std::cout << health << '\n';
	}

	return 0;
}