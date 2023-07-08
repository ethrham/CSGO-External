#include "Memory.h"
#include <TlHelp32.h>


void Memory::GetProcessId(const std::string_view process_name)
{
	auto process_entry = PROCESSENTRY32{};
	process_entry.dwSize = sizeof(PROCESSENTRY32);
	const auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	do
	{
		if (!process_name.compare(process_entry.szExeFile))
		{
			process_id = process_entry.th32ProcessID;
			break;
		}
	}
	while (Process32Next(snapshot, &process_entry));

	if (snapshot)
		CloseHandle(snapshot);
}

std::uintptr_t Memory::GetModuleBaseAddress(const std::string_view module_name)
{
	auto module_entry = MODULEENTRY32{};
	module_entry.dwSize = sizeof(MODULEENTRY32);
	const auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, process_id);

	std::uintptr_t module_address = 0;

	do
	{
		if (!module_name.compare(module_entry.szModule))
		{
			module_address = reinterpret_cast<uintptr_t>(module_entry.modBaseAddr);
		}
	}
	while (Module32Next(snapshot, &module_entry));

	if (snapshot)
		CloseHandle(snapshot);

	return module_address;
}

void Memory::OpenHandle()
{
	process_handle = OpenProcess(PROCESS_ALL_ACCESS, 0, process_id);
}

void Memory::Close_Handle()
{
	if (process_handle)
		CloseHandle(process_handle);
}
