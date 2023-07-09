#include "Features.h"
#include "Memory.h"
#include "Offsets.h"

void Features::Triggerbot(unsigned local_player)
{
	if (!GetAsyncKeyState(VK_SHIFT))
		return;

	if (Memory::Read<int32_t>(local_player + Offsets::m_iHealth) <= 0)
		return;

	const auto crosshair_id = Memory::Read<int32_t>(local_player + Offsets::m_iCrosshairId);

	if (crosshair_id < 0 || crosshair_id > 64)
		return;

	const auto crosshair_player = Memory::Read<uintptr_t>(Memory::client + Offsets::dwEntityList + (crosshair_id - 1) * 0x10);

	if (Memory::Read<int32_t>(crosshair_player + Offsets::m_iHealth) <= 0)
		return;

	if (Memory::Read<int32_t>(crosshair_id + Offsets::m_iTeamNum) == Memory::Read<uint32_t>(local_player + Offsets::m_iTeamNum))
		return;

	Memory::Write<uintptr_t>(Memory::client + Offsets::dwForceAttack, 6);
}
