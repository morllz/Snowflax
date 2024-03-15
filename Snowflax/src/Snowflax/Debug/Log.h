#pragma once

#include "Snowflax/Core.h"


#ifdef SFX_FLAG_DEBUG

#include <memory>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

// ----------- Default Logging Configuration -----------

#define SFX_LOG_LEVEL		   spdlog::level::level_enum::trace
#define SFX_LOG_ENGINE_PATTERN %+
#define SFX_LOG_CLIENT_PATTERN %+

// -----------------------------------------------------


namespace Snowflax {

	class SNOWFLAX_API Log {
	public:
		static int Init() {

		}

		static std::shared_ptr<spdlog::logger> GetEngineConsole() {
			return m_sEngineLogger;
		}
		static std::shared_ptr<spdlog::logger> GetClientConsole() {
			return m_sClientLogger;
		}

	private:
		static std::shared_ptr<spdlog::logger> m_sEngineLogger;
		static std::shared_ptr<spdlog::logger> m_sClientLogger;

	};

};

#endif // SFX_FLAG_DEBUG