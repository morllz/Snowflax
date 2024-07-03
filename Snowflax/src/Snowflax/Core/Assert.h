#pragma once

#include "Base.h"
#include <filesystem>

#ifdef SFLX_ENABLE_ASSERTS
	#define SFLX_ASSERT_IMPL(check, msg, ...) do { if(!(check)) { SFLX_LOG_ERROR(msg, __VA_ARGS__); SFLX_DEBUGBREAK(); } } while(0)
	#define SFLX_ASSERT_WITH_MSG(check, ...) SFLX_ASSERT_IMPL(check, "Assertion failed: {0}", __VA_ARGS__)
	#define SFLX_ASSERT_NO_MSG(check) SFLX_ASSERT_IMPL(check, "Assertion '{0}' failed at {1}:{2}", SFLX_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define SFLX_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define SFLX_ASSERT_GET_MACRO(...) SFLX_EXPAND_MACRO( SFLX_ASSERT_GET_MACRO_NAME(__VA_ARGS__, SFLX_ASSERT_WITH_MSG, SFLX_ASSERT_NO_MSG) )

	#define SFLX_ASSERT(...) SFLX_EXPAND_MACRO( SFLX_ASSERT_GET_MACRO(__VA_ARGS__)(__VA_ARGS__) )

#else
	#define SFLX_ASSERT(...) SFLX_EXPAND_MACRO(SFLX_MACRO_GET_FIRST_ARG(__VA_ARGS__))
#endif
