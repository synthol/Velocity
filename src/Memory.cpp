#include "Application.hpp"

namespace Velocity
{
	template <typename T>
	T Memory::Read(const unsigned long address) const
	{
		T buffer{};
		ReadProcessMemory(m_ProcessHandle, reinterpret_cast<const void*>(address), &buffer, sizeof(buffer), 0);
		return buffer;
	}

	template <typename T>
	void Memory::Write(const unsigned long address, T buffer) const
	{
		WriteProcessMemory(m_ProcessHandle, reinterpret_cast<void*>(address), &buffer, sizeof(buffer), 0);
	}

	void Memory::HealthGlowEsp() const
	{
		const unsigned int localPlayer{ Read<unsigned int>(m_ClientAddress + m_LocalPlayer) };
		const unsigned int glowObject{ Read<unsigned int>(m_ClientAddress + m_GlowObject) };
		const unsigned int localTeam{ Read<unsigned int>(localPlayer + m_Team) };

		for (unsigned short int i = 0; i < 32; i++)
		{
			const unsigned int entityList{ Read<unsigned int>(m_ClientAddress + m_EntityList + i * 0x10) };
			const unsigned int team{ Read<unsigned int>(entityList + m_Team) };
			const unsigned int glowIndex{ Read<unsigned int>(entityList + m_GlowIndex)};
			const unsigned int health{ Read<unsigned int>(entityList + m_Health) };
			const bool dormant{ Read<bool>(entityList + m_Dormant) };

			if (team != localTeam && health >= 75)
			{
				Write<const float>(glowObject + glowIndex * 0x38 + 0x8, 0);
				Write<const float>(glowObject + glowIndex * 0x38 + 0xC, 255);
				Write<const float>(glowObject + glowIndex * 0x38 + 0x10, 0);
				Write<const float>(glowObject + glowIndex * 0x38 + 0x14, 1);
				Write<const bool>(glowObject + glowIndex * 0x38 + 0x27, true);
				Write<const bool>(glowObject + glowIndex * 0x38 + 0x28, true);
			}
			else if (team != localTeam && health >= 50 && health < 75)
			{
				Write<const float>(glowObject + glowIndex * 0x38 + 0x8, 255);
				Write<const float>(glowObject + glowIndex * 0x38 + 0xC, 255);
				Write<const float>(glowObject + glowIndex * 0x38 + 0x10, 0);
				Write<const float>(glowObject + glowIndex * 0x38 + 0x14, 1);
				Write<const bool>(glowObject + glowIndex * 0x38 + 0x27, true);
				Write<const bool>(glowObject + glowIndex * 0x38 + 0x28, true);
			}
			else if (team != localTeam && health < 50)
			{
				Write<const float>(glowObject + glowIndex * 0x38 + 0x8, 255);
				Write<const float>(glowObject + glowIndex * 0x38 + 0xC, 0);
				Write<const float>(glowObject + glowIndex * 0x38 + 0x10, 0);
				Write<const float>(glowObject + glowIndex * 0x38 + 0x14, 1);
				Write<const bool>(glowObject + glowIndex * 0x38 + 0x27, true);
				Write<const bool>(glowObject + glowIndex * 0x38 + 0x28, true);
			}
			else
			{
				Write<const float>(glowObject + glowIndex * 0x38 + 0x8, 255);
				Write<const float>(glowObject + glowIndex * 0x38 + 0xC, 255);
				Write<const float>(glowObject + glowIndex * 0x38 + 0x10, 255);
				Write<const float>(glowObject + glowIndex * 0x38 + 0x14, 1);
				Write<const bool>(glowObject + glowIndex * 0x38 + 0x27, true);
				Write<const bool>(glowObject + glowIndex * 0x38 + 0x28, true);
			}
		}
	}
}