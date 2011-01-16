solution "ArxFatalis"
	configurations { "Debug", "Release" }
	location "build"

	includedirs
	{
		"Include/OtherLibs",
		"Include",
	}

	libdirs
	{
		"lib/otherlibs",
		"lib",
	}

	configuration "Debug"
		defines { "_DEBUG" }
		flags { "Symbols" }

	configuration "Release"
		defines { "NDEBUG" }
		flags { "OptimizeSpeed" }

	configuration { "windows" }
		defines { "WIN32", "_WINDOWS", "_CRT_SECURE_NO_WARNINGS" }
		includedirs
		{
			"DX/include",
		}
		libdirs
		{
			"DX/lib",
		}

	project "ArxCommon"
		kind "StaticLib"
		language "C++"
		flags { "Unicode" }
		defines { "_LIB", "_UNICODE" }
		targetdir "lib"
		files
		{
			"ArxCommon/*.cpp",
		}

	project "Athena"
		kind "SharedLib"
		language "C++"
		defines { "_USRDLL", "_MBCS", "ATHENA_EXPORTS", "AAL_APIDLL" }
		targetdir "../game"
		files
		{
			"Athena/*.cpp",
			"Athena/*.h",
		}
		excludes
		{
			"Athena/Athena_Stream_ASF.cpp",
			"Athena/Athena_Track.cpp",
		}
		links
		{
			"ArxCommon",
			"HERMES",
			"ARX_SCRIPT_DEBUGGER",
		}

		configuration "windows"
			linkoptions { "/NODEFAULTLIB:LIBC" }

	project "EErie"
		kind "StaticLib"
		language "C++"
		defines { "_LIB", "_MBCS" }
		targetdir "lib"
		files
		{
			"EERIE/*.cpp",
		}

	project "HERMES"
		kind "StaticLib"
		language "C++"
		defines { "_LIB", "_MBCS" }
		targetdir "lib"
		files
		{
			"HERMES/*.cpp",
			"HERMES/HERMESnet.rc",
		}

	project "Mercury"
		kind "StaticLib"
		language "C++"
		defines { "_LIB", "_MBCS" }
		targetdir "lib"
		files
		{
			"Mercury/*.cpp",
		}

	project "MINOS"
		kind "StaticLib"
		language "C++"
		defines { "_LIB", "_MBCS" }
		targetdir "lib"
		files
		{
			"MINOS/*.cpp",
		}

	project "DANAE"
		kind "WindowedApp"
		language "C++"
		flags { "Unicode" }
		defines { "_UNICODE" }
		targetdir "../game"
		targetname "arx"
		files
		{
			"DANAE/*.cpp",
			"DANAE/*.h",
			"DANAE/*.rc",
		}
		links
		{
			"ArxCommon",
			"Athena",
			"EErie",
			"HERMES",
			"Mercury",
			"MINOS",
			--"ARX_SCRIPT_DEBUGGER",
		}

	project "ARX_SCRIPT_DEBUGGER"
		kind "SharedLib"
		language "C++"
		defines { "_USRDLL", "_MBCS", "ARX_SCRIPT_DEBUGGER_EXPORTS", "APIDLL" }
		files
		{
			"DANAE_Debugger/resource.h",
			--"DANAE_Debugger/SCRIPT_DEBUGGER.def",
			"DANAE_Debugger/SCRIPT_DEBUGGER.rc",
			"DANAE_Debugger/SCRIPT_DEBUGGER_Dialog.cpp",
			"DANAE_Debugger/SCRIPT_DEBUGGER_Dialog.h",
		}

		configuration "Debug"
			targetdir "DANAE/Debug"

		configuration "Release"
			targetdir "DANAE/Release"

		configuration "windows"
			links
			{
				"comctl32",
			}
