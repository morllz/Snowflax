#pragma once

#ifdef SFX_PLATFORM_WINDOWS

#else
	#error Snowflax currently only supports Windows!
#endif //SFX_PLATFORM_WINDOWS


#ifdef SFX_DEBUG
	#define SFX_FLAG_DEBUG
#endif // SFX_DEBUG