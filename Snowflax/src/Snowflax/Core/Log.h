#pragma once

// SFX_ENABLE_LOGGING
#ifdef SFX_ENABLE_LOGGING

#include "SFXpch.h"

#include "spdlog/sinks/stdout_color_sinks.h"

// ------------- LOGGING PATTERN --------------------------
#define SFX_CORE_LOG_PATTERN "%T.%e [%n] %^%v%$"
// --------------------------------------------------------


#ifdef SFX_CORE
#define SFX_GET_LOGGER Snowflax::Log::GetCoreConsole()
#endif // SFX_CORE
#ifndef SFX_CORE
#define SFX_GET_LOGGER Snowflax::Log::GetClientConsole()
#endif // !SFX_CORE


#define SFX_LOG_INFO(...) SFX_GET_LOGGER()->info(...)
#define SFX_LOG_DEBUG(...) SFX_GET_LOGGER()->debug(...)
#define SFX_LOG_WARN(...) SFX_GET_LOGGER()->warn(...)
#define SFX_LOG_ERROR(...)	SFX_GET_LOGGER()->error(...)
#define SFX_LOG_CRITICAL(...) SFX_GET_LOGGER()->critical(...)


namespace Snowflax {

	class Log {
	public:

		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreConsole();
		static std::shared_ptr<spdlog::logger>& GetClientConsole();

	private:
		inline static std::shared_ptr<spdlog::logger> m_sCoreLogger;
		inline static std::shared_ptr<spdlog::logger> m_sClientLogger;
	};
}

#else

#define SFX_LOG_INFO(...)	
#define SFX_LOG_DEBUG(...)	
#define SFX_LOG_WARN(...)	
#define SFX_LOG_ERROR(...)	
#define SFX_LOG_CRITICAL(...)

#endif
// !SFX_ENABLE_LOGGING