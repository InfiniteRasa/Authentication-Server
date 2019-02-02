-- infinite rasa
-- authentication server.lua

workspace "InfiniteRasa"
	configurations { "Debug", "Release" }

project "irauth"
	kind "ConsoleApp"
	language "C++"
	targetdir "bin/%{cfg.buildcfg}"
	objdir "build/%{cfg.buildcfg}"
	
	files { 
		"src/main.cpp",
		"src/CryptManager.h",
		"src/CryptManager.cpp",
		"src/DBManager.h",
		"src/DBManager.cpp",
		"src/INIParser.h",
		"src/INIParser.cpp",
		"src/MD5.h",
		"src/MD5.cpp",
		"src/NetManager.h",
		"src/NetManager.cpp",
		"src/NetUtils.h",
		"src/NetUtils.cpp",
		"src/SessionManager.h",
		"src/SessionManager.cpp",
		"src/ThreadsUtils.h",
		"src/ThreadsUtils.cpp",
		"src/NetObjects.h",
		"src/MessageHandler.h",
		"src/MessageHandler.cpp",
		"libs/minINI/minIni.c"
	}

	staticruntime "On"
	flags { "MultiProcessorCompile", "FatalCompileWarnings" }
	defines { "_CRT_SECURE_NO_WARNINGS", "_CRT_NO_TIME_T", "INI_ANSIONLY" }
	
	filter "system:Windows"
		includedirs { "libs/pthreads/include", "libs/mariadb/include", "libs/minINI" }
		libdirs { "libs/pthreads/lib", "libs/mariadb/lib" }
		links { "ws2_32", "pthreadVC2", "libmariadb" }
	
	filter "system:Linux"
		includedirs { "libs/minINI", "/usr/include/mysql" }
		libdirs { "/usr/lib/mysql", "/usr/lib/arm-linux-gnueabihf" } 
		links { "pthread", "mariadbclient" }
		
	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"