#include "Application.hpp"

namespace Velocity
{
	Application::Application()
		: m_SnapshotHandle(&m_SnapshotHandle)
	{
		const unsigned int processId{ GetProcess(L"csgo.exe") };
		m_Memory.m_ClientAddress = GetModule(processId, L"client.dll");
		m_Memory.m_ProcessHandle = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, processId);

		while (processId && m_Memory.m_ClientAddress && m_Memory.m_ProcessHandle)
		{
			m_Memory.HealthGlowEsp();
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}

	Application::~Application()
	{
		CloseHandle(m_SnapshotHandle);
	}

	unsigned int Application::GetProcess(const wchar_t* processName) const
	{
		unsigned int processId{};
		m_SnapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		
		if (m_SnapshotHandle != INVALID_HANDLE_VALUE)
		{
			PROCESSENTRY32 processEntry{ sizeof(processEntry) };

			if (Process32First(m_SnapshotHandle, &processEntry))
			{
				do
				{
					if (!wcscmp(processEntry.szExeFile, processName))
					{
						processId = processEntry.th32ProcessID;
						break;
					}
				} while(Process32Next(m_SnapshotHandle, &processEntry));
			}
		}

		return processId;
	}

	unsigned int Application::GetModule(const unsigned int processId, const wchar_t* moduleName) const
	{
		unsigned int moduleAddress{};
		m_SnapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);

		if (m_SnapshotHandle != INVALID_HANDLE_VALUE)
		{
			MODULEENTRY32 moduleEntry{ sizeof(moduleEntry) };

			if (Module32First(m_SnapshotHandle, &moduleEntry))
			{
				do
				{
					if (!wcscmp(moduleEntry.szModule, moduleName))
					{
						moduleAddress = reinterpret_cast<const unsigned int>(moduleEntry.modBaseAddr);
						break;
					}
				} while (Module32Next(m_SnapshotHandle, &moduleEntry));
			}
		}

		return moduleAddress;
	}
}
