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

include "dependencies/GLFW"

project 'Ts3Tool'
	location ''
	language 'C++'
	cppdialect 'C++17'
	systemversion 'latest'
	targetsuffix ('-%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg:lower()}')

	debugcommand (ts3_path .. '\\ts3client_win64.exe')
	debugdir (ts3_path)
	debugargs {'-console'}

	defines {
	    "IMGUI_IMPL_OPENGL_LOADER_GLAD",
        "GLFW_INCLUDE_NONE",
	}

	links {
	    "GLFW"
	}

	filter 'configurations:Debug'
		runtime "Debug"
		symbols "on"

	filter 'configurations:Release'
		runtime "Release"
		optimize "on"

	filter {}

	targetdir(build_dir)
	objdir('%{wks.location}/build/bin-int/%{cfg.buildcfg:lower()}')

	includedirs {
		'%{wks.location}/src',								-- plugin
		'%{wks.location}/dependencies/glad/include',        -- glad
		'%{wks.location}/dependencies/glfw/include',        -- glfw
		'%{wks.location}/dependencies/imgui',               -- glfw
		'%{wks.location}/dependencies/spdlog/include',		-- spdlog
		'%{wks.location}/dependencies/ts3/include',			-- ts3
	}

	files {
	    -- plugin
		'%{wks.location}/src/**',
		-- glad
		'%{wks.location}/dependencies/glad/**',
		-- imgui
		'%{wks.location}/dependencies/imgui/imconfig.h',
		'%{wks.location}/dependencies/imgui/imgui.h',
		'%{wks.location}/dependencies/imgui/imgui.cpp',
		'%{wks.location}/dependencies/imgui/imgui_demo.cpp',
		'%{wks.location}/dependencies/imgui/imgui_draw.cpp',
		'%{wks.location}/dependencies/imgui/imgui_internal.h',
		'%{wks.location}/dependencies/imgui/imgui_widgets.cpp',
		'%{wks.location}/dependencies/imgui/imstb_rectpack.h',
		'%{wks.location}/dependencies/imgui/imstb_textedit.h',
		'%{wks.location}/dependencies/imgui/imstb_truetype.h',
		'%{wks.location}/dependencies/imgui/examples/imgui_impl_glfw.cpp',
		'%{wks.location}/dependencies/imgui/examples/imgui_impl_glfw.h',
		'%{wks.location}/dependencies/imgui/examples/imgui_impl_opengl3.cpp',
		'%{wks.location}/dependencies/imgui/examples/imgui_impl_opengl3.h',
		-- spdlog
	}

