#pragma once


#include <memory>

#include "Snowflax/Core.h"
#include "Snowflax/Utils.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

// ------------- LOGGING PATTERNS -------------------------
constexpr auto SFX_CORE_LOG_PATTERN = "%T.%e [%n] %^%v%$";
// --------------------------------------------------------


#ifdef SFX_CORE
#define SFX_GET_LOGGER Snowflax::Log::GetCoreConsole()
#endif // SFX_CORE
#ifndef SFX_CORE
#define SFX_GET_LOGGER Snowflax::Log::GetClientConsole()
#endif // !SFX_CORE

#define SFX_LOG_INFO(...)		SFX_GET_LOGGER->info(__VA_ARGS__)
#define SFX_LOG_DEBUG(...)		SFX_GET_LOGGER->debug(__VA_ARGS__)
#define SFX_LOG_WARN(...)		SFX_GET_LOGGER->warn(__VA_ARGS__)
#define SFX_LOG_ERROR(...)		SFX_GET_LOGGER->error(__VA_ARGS__)
#define SFX_LOG_CRITICAL(...)	SFX_GET_LOGGER->critical(__VA_ARGS__)


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
