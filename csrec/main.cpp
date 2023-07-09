#include <iostream>
#include <thread>

#include "Memory.h"
#include "Offsets.h"
#include "Features.h"

// I PAID FOR THE RAM STICK NO STUPID APPLICATION CAN TELL ME WHAT ADDRESS I CAN AND CAN'T READ

int main()
{
	const Memory memory_manager("csgo.exe");
	const std::uintptr_t client = memory_manager.GetModuleBaseAddress("client.dll");

	while (true)
	{
		const auto local_player = memory_manager.Read<uintptr_t>(client + Offsets::dwLocalPlayer);

		Features::Bunnyhop(local_player, client, memory_manager);
		Features::Triggerbot(local_player, client, memory_manager);

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}