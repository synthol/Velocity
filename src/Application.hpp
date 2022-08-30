#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <thread>
#include "Memory.hpp"

namespace Velocity
{
	class Application
	{
	private:
		unsigned int GetProcess(const wchar_t* processName) const;
		unsigned int GetModule(const unsigned int processId, const wchar_t* moduleName) const;
	private:
		void*&& m_SnapshotHandle;
		const Memory& m_Memory{};
	public:
		Application();
		~Application();
	};
}
