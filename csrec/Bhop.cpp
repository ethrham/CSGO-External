#include <iostream>

#include "Features.h"
#include "Memory.h"
#include "Offsets.h"

void Features::Bunnyhop(unsigned local_player)
{
	if (GetAsyncKeyState(VK_SPACE))
	{
		const auto local_flags = Memory::Read<BYTE>(local_player + Offsets::m_fFlags);

		if (local_flags & 1)
			Memory::Write<DWORD>(Memory::client + Offsets::dwForceJump, 6);
		else
			Memory::Write<DWORD>(Memory::client + Offsets::dwForceJump, 0);
	}
}
