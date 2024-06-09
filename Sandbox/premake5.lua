project "Sandbox"
	kind "ConsoleApp"
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
		"%{wks.location}/Snowflax/src",
		"%{wks.location}/Snowflax/vendor/spdlog/include"
	}

	filter "system:windows"
		systemversion "latest"

	links {
		"Snowflax"
	}

	defines {
		"SFX_PLATFORM_WINDOWS"
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