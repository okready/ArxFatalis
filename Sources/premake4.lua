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
		flags { "Symbols" }
		defines { "_DEBUG" }

	configuration "Release"
		flags { "OptimizeSpeed" }
		defines { "NDEBUG" }

	configuration { "windows" }
		flags { "StaticRuntime", "WinMain" }
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
			"Include/ARX_Common.h",
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
			"Include/Athena*",
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
			"Include/EERIE*",
			"Include/TheoData.h",
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
			"Include/HERMES*",
			"Include/resource.h",
			"Include/ResourceHERMESnet.h",
		}

	project "Mercury"
		kind "StaticLib"
		language "C++"
		defines { "_LIB", "_MBCS" }
		targetdir "lib"
		files
		{
			"Mercury/*.cpp",
			"Include/Mercury*",
		}

	project "MINOS"
		kind "StaticLib"
		language "C++"
		defines { "_LIB", "_MBCS" }
		targetdir "lib"
		files
		{
			"MINOS/*.cpp",
			"Include/Minos*",
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
			"DANAE/DANAE.rc",
			"Include/ARX*",
			"Include/Danae*",
			"Include/DANAE*",
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
			"implode",
		}

		configuration "windows"
			links
			{
				"zlib",
				"jpeglib",
				"dinput",
				"wsock32",
				"dxguid",
				"dsound",
				"winmm",
				"comctl32",
				"ddraw",
				"advapi32",
			}
			linkoptions { "/NODEFAULTLIB:LIBC" }

		configuration "not windows"
			links
			{
				"z",
				"jpeg",
			}

	project "ARX_SCRIPT_DEBUGGER"
		kind "SharedLib"
		language "C++"
		defines { "_USRDLL", "_MBCS", "ARX_SCRIPT_DEBUGGER_EXPORTS", "APIDLL" }
		targetdir "../game"
		files
		{
			"DANAE_Debugger/resource.h",
			--"DANAE_Debugger/SCRIPT_DEBUGGER.def",
			"DANAE_Debugger/SCRIPT_DEBUGGER.rc",
			"DANAE_Debugger/SCRIPT_DEBUGGER_Dialog.cpp",
			"DANAE_Debugger/SCRIPT_DEBUGGER_Dialog.h",
		}

		configuration "windows"
			links
			{
				"comctl32",
			}
