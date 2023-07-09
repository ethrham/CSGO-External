#include "Features.h"
#include "Memory.h"
#include "Offsets.h"

void Features::Triggerbot(unsigned local_player, std::uintptr_t client, const Memory& memory_manager)
{
	if (!GetAsyncKeyState(VK_SHIFT))
		return;

	if (memory_manager.Read<int32_t>(local_player + Offsets::m_iHealth) <= 0)
		return;

	const auto crosshair_id = memory_manager.Read<int32_t>(local_player + Offsets::m_iCrosshairId);

	if (crosshair_id < 0 || crosshair_id > 64)
		return;

	const auto crosshair_player = memory_manager.Read<uintptr_t>(client + Offsets::dwEntityList + (crosshair_id - 1) * 0x10);

	if (memory_manager.Read<int32_t>(crosshair_player + Offsets::m_iHealth) <= 0)
		return;

	if (memory_manager.Read<int32_t>(crosshair_id + Offsets::m_iTeamNum) == memory_manager.Read<uint32_t>(local_player + Offsets::m_iTeamNum))
		return;

	memory_manager.Write<uintptr_t>(client + Offsets::dwForceAttack, 6);
}
