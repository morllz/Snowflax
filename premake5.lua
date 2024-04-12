workspace "Snowflax"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

	files {
		"premake5.lua",
		".gitignore",
		".gitmodules"
	}

	startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


-- Project "Snowflax"

project "Snowflax"
	location "Snowflax"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Snowflax/src",
		"Snowflax/vendor/spdlog/include"
	}

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

-- Project "Snowflax"


-- Project "Sandbox"
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Snowflax/src",
		"Snowflax/vendor/spdlog/include"
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

-- Project "Sandbox"

-- Project "SnowflaxTest"
project "SnowflaxTest"
	location "SnowflaxTest"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/googletest/googletest/**.h",
        "%{prj.name}/vendor/googletest/googletest/**.hpp",
        "%{prj.name}/vendor/googletest/googletest/src/gtest-all.cc"
	}

	includedirs {
		"Snowflax/src",
		"Snowflax/vendor/spdlog/include",
		"%{prj.name}/vendor/googletest/googletest/include",
		"%{prj.name}/vendor/googletest/googletest/"

	}

	filter "system:windows"
		systemversion "latest"

	links {
		"Snowflax"
	}

	defines {
		"SFX_PLATFORM_WINDOWS",
		"SFX_DEBUG",
		"SFX_TEST"
	}

	flags { "UnitTest" }

	symbols "On"

-- Project "SnowflaxTest"