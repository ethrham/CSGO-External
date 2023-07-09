#include <iostream>

#include "Features.h"
#include "Memory.h"
#include "Offsets.h"

void Features::Bunnyhop(const unsigned local_player, std::uintptr_t client, const Memory& memory_manager)
{
	if (GetAsyncKeyState(VK_SPACE))
	{
		if (memory_manager.Read<BYTE>(local_player + Offsets::m_fFlags) & 1)
			memory_manager.Write<DWORD>(client + Offsets::dwForceJump, 6);
		else
			memory_manager.Write<DWORD>(client + Offsets::dwForceJump, 0);
	}
}
