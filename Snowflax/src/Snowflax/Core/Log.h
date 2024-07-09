#pragma once

#include "Base.h"

// SFLX_ENABLE_LOGGING
#ifdef SFLX_ENABLE_LOGGING

#include "SFLXpch.h"

#pragma warning(push, 0)
#include "spdlog/sinks/stdout_color_sinks.h"
#pragma warning(pop)

// ------------- LOGGING PATTERN --------------------------
#define SFLX_CORE_LOG_PATTERN "%T.%e [%n] %^%v%$"
// --------------------------------------------------------


#ifdef SFLX_CORE
#define SFLX_GET_LOGGER() Snowflax::Log::GetCoreConsole()
#endif // SFLX_CORE
#ifndef SFLX_CORE
#define SFLX_GET_LOGGER() Snowflax::Log::GetClientConsole()
#endif // !SFLX_CORE

#define SFLX_LOG_TRACE(...)		SFLX_GET_LOGGER()->trace(__VA_ARGS__)
#define SFLX_LOG_INFO(...)		SFLX_GET_LOGGER()->info(__VA_ARGS__)
#define SFLX_LOG_DEBUG(...)		SFLX_GET_LOGGER()->debug(__VA_ARGS__)
#define SFLX_LOG_WARN(...)		SFLX_GET_LOGGER()->warn(__VA_ARGS__)
#define SFLX_LOG_ERROR(...)		SFLX_GET_LOGGER()->error(__VA_ARGS__)
#define SFLX_LOG_CRITICAL(...)	SFLX_GET_LOGGER()->critical(__VA_ARGS__)


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

#define SFLX_LOG_TRACE(...)
#define SFLX_LOG_INFO(...)	
#define SFLX_LOG_DEBUG(...)	
#define SFLX_LOG_WARN(...)	
#define SFLX_LOG_ERROR(...)	
#define SFLX_LOG_CRITICAL(...)

#endif
// !SFLX_ENABLE_LOGGING