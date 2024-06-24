project "SnowflaxTest"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"src/**.h",
		"src/**.cpp",
		"vendor/googletest/googletest/**.h",
        "vendor/googletest/googletest/**.hpp",
        "vendor/googletest/googletest/src/gtest-all.cc"
	}

	includedirs {
		"%{wks.location}/Snowflax/src",
		"%{wks.location}/Snowflax/vendor/spdlog/include",
		"vendor/googletest/googletest/include",
		"vendor/googletest/googletest/"
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