#pragma once


#ifdef SFX_FLAG_DEBUG

#include <memory>

#include "Snowflax/Core.h"
#include "Snowflax/Utils.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

// ------------- LOGGING PATTERNS ----------------------
#define SFX_CORE_LOG_PATTERN "%T.%e [%n] %^%v%$"
// -----------------------------------------------------

#define DEF_COLOR_SINK_MT(name, level, pattern, R, G, B) \
	auto name = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();\
	name->set_level(level);\
	name->set_pattern(pattern);\
	name->set_color(level, COLOR16_FROM_RGB(R, G, B))


namespace Snowflax {
	namespace Debug {

		class SNOWFLAX_API Log {
		public:
			static int Init();

			static std::shared_ptr<spdlog::logger> GetCoreConsole();
			static std::shared_ptr<spdlog::logger> GetClientConsole();

		private:
			static std::shared_ptr<spdlog::logger> m_sCoreLogger;
			static std::shared_ptr<spdlog::logger> m_sClientLogger;
		};
	}
};

#endif // SFX_FLAG_DEBUG