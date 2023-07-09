#pragma once
#include <cstdint>

class Memory;

namespace Features
{
	void Bunnyhop(unsigned local_player, std::uintptr_t client, const Memory& memory_manager);
	void Triggerbot(unsigned local_player, std::uintptr_t client, const Memory& memory_manager);
}
