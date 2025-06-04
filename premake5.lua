workspace "game_engine"
	architecture "x64"
	
	configurations{
		"Debug",
		"Release",
		"Dist"
	}
	
outputdir = "%{cfg.buidcfg}-%{cfg.system}-%{cfg.architecture}"
	
-- Include directories relate to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "game_engine/vendor/GLFW/include"
IncludeDir["Glad"] = "game_engine/vendor/Glad/include"

include "game_engine/vendor/GLFW"
include "game_engine/vendor/Glad"
	
project "game_engine"
	location "game_engine"
	kind "SharedLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "gepch.h"
	pchsource "game_engine/src/gepch.cpp"
	
	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
	}
	
	links{
		"GLFW",
		"Glad",
		"opengl32.lib"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines{
			"GE_PLATFORM_WINDOWS",
			"GE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		
		postbuildcommands{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
		
	filter "configurations:Debug"
		defines "GE_DEBUG"
		buildoptions "/MDd"
		symbols "On"
		
	filter "configurations:Release"
		defines "GE_RELEASE"
		buildoptions "/MD"
		optimize "On"
		
	filter "configurations:Dist"
		defines "GE_DIST"
		buildoptions "/MD"
		optimize "On"
		
	filter "action:vs*"
		buildoptions { "/utf-8" }
		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs{
		"game_engine/vendor/spdlog/include",
		"game_engine/src"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines{
			"GE_PLATFORM_WINDOWS"
		}
		
	links{
		"game_engine"
	}
		
	filter "configurations:Debug"
		defines "GE_DEBUG"
		buildoptions "/MDd"
		symbols "On"
		
	filter "configurations:Release"
		defines "GE_RELEASE"
		buildoptions "/MD"
		optimize "On"
		
	filter "configurations:Dist"
		defines "GE_DIST"
		buildoptions "/MD"
		optimize "On"
		
	filter "action:vs*"
		buildoptions { "/utf-8" }