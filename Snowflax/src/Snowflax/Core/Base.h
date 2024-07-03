#pragma once

#define BIT(x) (1 << x)

#define SFLX_MACRO_GET_FIRST_ARG(N, ...) N
#define SFLX_MACRO_POP_FIRST_ARG(N, ...) __VA_ARGS__

#define SFLX_EXPAND_MACRO(x) x
#define SFLX_STRINGIFY_MACRO(x) #x

#ifdef SFLX_DEBUG
	#if defined(SFLX_PLATFORM_WINDOWS)
		#define SFLX_DEBUGBREAK() __debugbreak()
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define SFLX_ENABLE_ASSERTS
	#define SFLX_ENABLE_LOGGING
#else
	#define SFLX_DEBUGBREAK()
#endif

#ifdef SFLX_RELEASE
	#define SFLX_ENBALE_LOGGING
#endif

#include "SFLXpch.h"
#include "Log.h"
#include "Assert.h"


namespace Snowflax
{
	template<typename T>
	using Ref =  std::shared_ptr<T>;
	template<typename T, typename... Args>
	constexpr Ref<T> MakeRef(Args... _args)
	{
		return std::make_shared<T>(std::forward<Args>(_args)...);
	}
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename... Args>
	constexpr Scope<T> MakeScope(Args... _args)
	{
		return std::make_unique<T>(std::forward<Args>(_args)...);
	}
}