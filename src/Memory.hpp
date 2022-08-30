#pragma once

#include "Application.hpp"

namespace Velocity
{
	class Memory
	{
	private:
		template <typename T> T Read(const unsigned long address) const;
		template <typename T> void Write(const unsigned long address, T buffer) const;
	private:
		const unsigned int m_Dormant{/* Address */};
		const unsigned int m_EntityList{/* Address */};
		const unsigned int m_GlowObject{/* Address */};
		const unsigned int m_GlowIndex{/* Address */};
		const unsigned int m_Health{/* Address */};
		const unsigned int m_LocalPlayer{/* Address */};
		const unsigned int m_Team{/* Address */};
	public:
		void HealthGlowEsp() const;
	public:
		void*&& m_ProcessHandle{};
		unsigned int&& m_ClientAddress{};
	};
}
