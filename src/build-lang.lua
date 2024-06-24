workspace "Entropia"
	configurations { "run", "static-build", "dynamic-build" }
	startproject "Entropia-Core"

project "Entropia-Core"
	project "Entropia-Core"
	language "C++"
	location "build/entropia-core"
	entrypoint "main"
	
	files {
		"main.cpp",
		"Entropia/**/*.cpp",
		"include/AquIce/Entropia/*.hpp"
	}

	includedirs { "include/" }

	filter { "configurations:run" }
		kind "ConsoleApp"

	filter { "configurations:static-build" }
		kind "StaticLib"
		removefiles { "main.cpp" }

	filter { "configurations:dynamic-build" }
		kind "SharedLib"
		removefiles { "main.cpp" }