#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Pinata {

	class PINATA_API Log
	{
	public:

		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:

		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};
}

//Core Log macros
#define PTA_CORE_TRACE(...)		::Pinata::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PTA_CORE_DEBUG(...)		::Pinata::Log::GetCoreLogger()->debug(__VA_ARGS__)
#define PTA_CORE_INFO(...)		::Pinata::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PTA_CORE_WARN(...)		::Pinata::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PTA_CORE_ERROR(...)		::Pinata::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PTA_CORE_CRITICAL(...)	::Pinata::Log::GetCoreLogger()->critical(__VA_ARGS__)


// Clent Log macros
#define PTA_TRACE(...)			::Pinata::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PTA_DEBUG(...)			::Pinata::Log::GetClientLogger()->debug(__VA_ARGS__)
#define PTA_INFO(...)			::Pinata::Log::GetClientLogger()->info(__VA_ARGS__)
#define PTA_WARN(...)			::Pinata::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PTA_ERROR(...)			::Pinata::Log::GetClientLogger()->error(__VA_ARGS__)
#define PTA_CRITICAL(...)		::Pinata::Log::GetClientLogger()->critical(__VA_ARGS__)

