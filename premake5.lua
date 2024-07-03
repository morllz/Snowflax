include "./vendor/premake/custom/solution_items.lua"

workspace "Snowflax"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

	solution_items {
		"premake5.lua",
		".gitignore",
		".gitmodules"
	}

	startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Snowflax"
	include "Snowflax"
	include "Sandbox"

group "Dependencies"
	include "Snowflax/vendor/GLFW"