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
	kind "SharedLib"
	language "C++"

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
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

	defines {
		"SFX_PLATFORM_WINDOWS",
		"SFX_BUILD_DLL"
	}

	postbuildcommands {
		("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
	}

	filter "configurations:Debug"
		defines "SFX_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "SFX_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "SFX_DIST"
		optimize "On"

-- Project "Snowflax"


-- Project "Sandbox"
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		cppdialect "C++20"

	links {
		"Snowflax"
	}

	defines {
		"SFX_PLATFORM_WINDOWS"
	}

	filter "configurations:Debug"
		defines "SFX_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "SFX_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "SFX_DIST"
		optimize "On"

-- Project "Sandbox"

-- Project "SnowflaxTest"
project "SnowflaxTest"
	location "SnowflaxTest"
	kind "ConsoleApp"
	language "C++"

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
		cppdialect "C++20"

	defines {
		"SFX_PLATFORM_WINDOWS"
	}

	filter "configurations:Debug"
		defines "SFX_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "SFX_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "SFX_DIST"
		optimize "On"

-- Project "SnowflaxTest"