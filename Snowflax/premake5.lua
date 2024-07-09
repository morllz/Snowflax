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
		"vendor/spdlog/include",
		"vendor/GLFW/include",
		os.getenv("VULKAN_SDK") .. "/Include"
	}

	defines "SFLX_CORE"

	pchheader "SFLXpch.h"
	pchsource "src/SFLXpch.cpp"

	libdirs {
		os.getenv("VULKAN_SDK") .. "/Lib"
	}

	links {
		"GLFW",
		"vulkan-1"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"SFLX_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "SFLX_DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "SFLX_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "SFLX_DIST"
		optimize "on"