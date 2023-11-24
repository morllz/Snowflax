#pragma once

#include <string>
#include <functional>


#ifdef SFX_PLATFORM_WINDOWS
	#ifdef SFX_BUILD_DLL
		#define SNOWFLAX_API __declspec(dllexport)
	#else
		#define SNOWFLAX_API __declspec(dllimport)
	#endif // SFX_BUILD_DLL
#else
	#error Snowflax currently only supports Windows!
#endif //SFX_PLATFORM_WINDOWS


#ifdef SFX_DEBUG
	#define SFX_FLAG_DEBUG
#endif // SFX_DEBUG


#define BIT(x) (1 << x)