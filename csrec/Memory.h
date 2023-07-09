#pragma once
#include <Windows.h>
#include <string_view>
#include <cstdint>
#include <memory>
#include <TlHelp32.h>

class Memory
{
private:
	struct HandleDisposer
	{
		using pointer = HANDLE;

		void operator()(HANDLE handle) const
		{
			if (handle != nullptr || handle != INVALID_HANDLE_VALUE)
				CloseHandle(handle);
		}
	};

	using unique_handle = std::unique_ptr<HANDLE, HandleDisposer>;
	unique_handle process_handle;
	std::uint32_t process_id;

	std::uint32_t GetProcessID(std::string_view process_name)
	{
		auto processentry = PROCESSENTRY32{};
		const unique_handle snapshot_handle(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0));
		processentry.dwSize = sizeof(PROCESSENTRY32);

		while (Process32Next(snapshot_handle.get(), &processentry) == TRUE)
		{
			if (process_name.compare(processentry.szExeFile) == 0)
				return processentry.th32ProcessID;
		}

		return 0;
	}

	static unique_handle OpenProcessHandle(const std::uintptr_t process_flags, const std::uint32_t process_id)
	{
		unique_handle processhandle(OpenProcess(process_flags, false, process_id));
		return processhandle;
	}

public:
	Memory(std::string_view process_name)
	{
		process_id = this->GetProcessID(process_name);
		this->process_handle = OpenProcessHandle(PROCESS_ALL_ACCESS, process_id);

	}
	Memory(const Memory&) = delete;
	Memory& operator = (const Memory&) = delete;

	std::uintptr_t GetModuleBaseAddress(const std::string_view module_name) const
	{
		auto moduleentry = MODULEENTRY32{};
		const unique_handle snapshot_handle(CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, this->process_id));
		moduleentry.dwSize = sizeof(MODULEENTRY32);

		while(Module32Next(snapshot_handle.get(), &moduleentry) == TRUE)
		{
			if (module_name.compare(moduleentry.szModule) == 0)
				return reinterpret_cast<uintptr_t>(moduleentry.modBaseAddr);
		}

		return 0;
	}

	template <typename T>
	T Read(const std::uintptr_t address) const
	{
		T buffer;
		ReadProcessMemory(this->process_handle.get(), reinterpret_cast<LPVOID>(address), &buffer, sizeof(buffer), nullptr);
		return buffer;
	}

	template <typename T>
	void Write(const std::uintptr_t address, const T& buffer) const
	{
		WriteProcessMemory(this->process_handle.get(), reinterpret_cast<LPVOID>(address), &buffer, sizeof(buffer), nullptr);
	}
};
