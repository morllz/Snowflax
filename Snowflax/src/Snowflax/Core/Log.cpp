#include "SFLXpch.h"
#include "Log.h"

#ifdef SFLX_ENABLE_LOGGING

void Snowflax::Log::Init()
{
	auto coreSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	coreSink->set_pattern(SFLX_CORE_LOG_PATTERN);
	coreSink->set_level(spdlog::level::trace);
	coreSink->set_color(spdlog::level::trace, 8);
	coreSink->set_color(spdlog::level::info, 10);
	coreSink->set_color(spdlog::level::debug, 6);
	coreSink->set_color(spdlog::level::warn, 14);
	coreSink->set_color(spdlog::level::err, 12);
	coreSink->set_color(spdlog::level::critical, 4);

	m_sCoreLogger = std::make_shared<spdlog::logger>("Core", coreSink);
	m_sCoreLogger->set_level(spdlog::level::trace);

	auto clientSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	clientSink->set_pattern(SFLX_CORE_LOG_PATTERN);
	clientSink->set_level(spdlog::level::trace);
	clientSink->set_color(spdlog::level::trace, 8);
	clientSink->set_color(spdlog::level::info, 10);
	clientSink->set_color(spdlog::level::debug, 6);
	clientSink->set_color(spdlog::level::warn, 14);
	clientSink->set_color(spdlog::level::err, 12);
	clientSink->set_color(spdlog::level::critical, 4);

	m_sClientLogger = std::make_shared<spdlog::logger>("Client", clientSink);
	m_sClientLogger->set_level(spdlog::level::trace);
}

std::shared_ptr<spdlog::logger>& Snowflax::Log::GetCoreConsole()
{
	if (!m_sCoreLogger) Init();
	return m_sCoreLogger;
}

std::shared_ptr<spdlog::logger>& Snowflax::Log::GetClientConsole()
{
	if (!m_sClientLogger) Init();
	return m_sClientLogger;
}

#endif // SFLX_DIST