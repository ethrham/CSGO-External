#include <iostream>
#include <thread>

#include "Memory.h"
#include "Offsets.h"
#include "Features.h"

int main()
{
	Memory::GetProcessId("csgo.exe");
	Memory::client = Memory::GetModuleBaseAddress("client.dll");
	Memory::OpenHandle();

	while (true)
	{
		const auto local_player = Memory::Read<uintptr_t>(Memory::client + Offsets::dwLocalPlayer);

		Features::Bunnyhop(local_player);
		Features::Triggerbot(local_player);

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}