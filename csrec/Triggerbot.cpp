#include <iostream>

#include "Features.h"
#include "Offsets.h"

void Features::Triggerbot(unsigned local_player)
{
	if (!GetAsyncKeyState(VK_SHIFT))
		return;

	std::cout << "1" << std::endl;

	const auto local_health = Memory::Read<int32_t>(local_player + Offsets::m_iHealth);

	if (local_health <= 0)
		return;

	std::cout << "2" << std::endl;

	const auto crosshair_id = Memory::Read<int32_t>(local_player + Offsets::m_iCrosshairId);

	if (crosshair_id < 0 || crosshair_id > 64)
		return;

	std::cout << "3" << std::endl;

	const auto crosshair_player = Memory::Read<uintptr_t>(Memory::client + Offsets::dwEntityList + (crosshair_id - 1) * 0x10);

	if (Memory::Read<int32_t>(crosshair_player + Offsets::m_iHealth) <= 0)
		return;

	std::cout << "4" << std::endl;

	if (Memory::Read<int32_t>(crosshair_id + Offsets::m_iTeamNum) == Memory::Read<uint32_t>(local_player + Offsets::m_iTeamNum))
		return;

	std::cout << "5" << std::endl;

	Memory::Write<uintptr_t>(Memory::client + Offsets::dwForceAttack, 6);
}
