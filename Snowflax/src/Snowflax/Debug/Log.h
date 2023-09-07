#pragma once

#include "Snowflax/Core.h"


#ifdef SFX_FLAG_DEBUG

#include <memory>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

// ----------- Default Logging Configuration -----------

#define SFX_LOG_LEVEL		   spdlog::level::level_enum::trace
#define SFX_LOG_SYSTEM_PATTERN %+
#define SFX_LOG_CLIENT_PATTERN %+

// -----------------------------------------------------


namespace Snowflax {

	class SNOWFLAX_API Log {
	public:
		static int Init();

		static std::shared_ptr<spdlog::logger> GetSystemConsole();
		static std::shared_ptr<spdlog::logger> GetClientConsole();

	private:
		static std::shared_ptr<spdlog::logger> m_sSystemLogger;
		static std::shared_ptr<spdlog::logger> m_sClientLogger;

	};

};

#endif // SFX_FLAG_DEBUG