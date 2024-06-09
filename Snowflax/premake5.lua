project "Snowflax"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"src",
		"vendor/spdlog/include"
	}

	pchheader "SFXpch.h"
	pchsource "src/SFXpch.cpp"

	filter "system:windows"
		systemversion "latest"

	defines {
		"SFX_PLATFORM_WINDOWS",
		"SFX_CORE"
	}

	filter "configurations:Debug"
		defines "SFX_DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "SFX_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "SFX_DIST"
		optimize "on"