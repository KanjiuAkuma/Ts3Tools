-- Build folder, set it to ts3 plugin folder for better testing, you could also use a post build copy
build_dir = 'C:\\Users\\Kanjiu Akuma\\AppData\\Roaming\\TS3Client\\plugins'
-- Path to ts3 installation to be used for debugging
ts3_path = 'C:\\Users\\Kanjiu Akuma\\AppData\\Local\\TeamSpeak 3 Client'

workspace 'Ts3Tool'
	architecture 'x64'
	characterset ('MBCS')
	startproject 'Ts3Tool'
	kind 'SharedLib'

	configurations
	{
		'Debug',
		'Release',
	}

project 'Ts3Tool'
	location ''
	language 'C++'
	cppdialect 'C++17'
	systemversion 'latest'
	targetsuffix ('-%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg:lower()}')

	debugcommand (ts3_path .. '\\ts3client_win64.exe')
	debugdir (ts3_path)
	debugargs {'-console'}

	filter 'configurations:Debug'
		symbols 'Full'

	filter 'configurations:Release'
		optimize 'On'

	filter {}

	targetdir(build_dir)
	objdir('%{wks.location}/build/bin-int/%{cfg.buildcfg:lower()}')

	includedirs {
		'%{wks.location}/src',								-- plugin
		'%{wks.location}/dependencies/spdlog/include',		-- spdlog
		'%{wks.location}/dependencies/ts3/include',			-- ts3
	}

	files {
		'%{wks.location}/src/**',							-- plugin
	}

