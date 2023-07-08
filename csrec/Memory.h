#pragma once
#include <Windows.h>
#include <string_view>
#include <cstdint>

namespace Memory
{
	inline unsigned long process_id = 0;
	inline void* process_handle = nullptr;

	inline std::uintptr_t client = 0;

	void GetProcessId(std::string_view process_name);
	std::uintptr_t GetModuleBaseAddress(std::string_view module_name);

	void OpenHandle();
	void Close_Handle();

	template <typename T>
	T Read(uintptr_t offset)
	{
		T value;
		ReadProcessMemory(process_handle, reinterpret_cast<LPVOID>(offset), &value, sizeof(T), nullptr);
		return value;
	}

	template <typename T>
	void Write(std::uintptr_t address, T value)
	{
		WriteProcessMemory(process_handle, reinterpret_cast<LPVOID>(address), reinterpret_cast<LPCVOID>(&value), sizeof(T), nullptr);
	}
}
