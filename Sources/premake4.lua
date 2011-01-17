solution "ArxFatalis"
	if os.get() == "windows" then
		configurations { "DebugD3D", "ReleaseD3D", "DebugSDL", "ReleaseSDL" }
	else
		configurations { "Debug", "Release" }
	end

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

	configuration "not windows or *SDL"
		defines { "USE_SDL=1" }

	configuration "not windows"
		buildoptions { "`sdl-config --cflags`" }
		linkoptions { "`sdl-config --libs`" }

	configuration { "windows", "*SDL" }
		includedirs
		{
			-- SDL headers are stored in a separate folder to keep
			-- us from accidentally including them when we want to
			-- use system headers on non-Windows platforms.
			"Include/OtherLibs/SDL",
		}

	configuration "Debug*"
		flags { "Symbols" }
		defines { "_DEBUG" }

	configuration "Release*"
		flags { "OptimizeSpeed" }
		defines { "NDEBUG" }

	configuration "windows"
		flags { "WinMain" }
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
		uuid "9C5EA702-89FA-410A-99D9-7E69678273E2"
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
		uuid "A3E68F99-7ABE-4E8f-BEFE-E015B9648B36"
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
		uuid "8FCD0821-34F6-4844-8583-974F99BAFC8D"
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
		uuid "EEFA95F9-40CA-403E-BCFD-4D114D4D924A"
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
		uuid "8AF8CBF1-ACC8-4662-921A-591A0096DDCC"
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
		uuid "132C430A-9DCD-4C4b-895D-DDEC7CB16B29"
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
		uuid "6AC9BAA9-D541-4B7B-820D-3C65D0E8FBAF"
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
				"libjpeg",
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

		-- SDL library link settings are already specified using
		-- sdl-config on non-Windows platforms.
		configuration { "windows", "*SDL" }
			links
			{
				"SDL",
				"SDLmain",
			}

	project "ARX_SCRIPT_DEBUGGER"
		uuid "1F80DAE1-4560-41FC-9D42-E13F82B0D60B"
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
