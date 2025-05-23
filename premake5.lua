workspace "game_engine"
	architecture "x64"
	
	configurations{
		"Debug",
		"Release",
		"Dist"
	}
	
outputdir = "%{cfg.buidcfg}-%{cfg.system}-%{cfg.architecture}"
	
project "game_engine"
	location "game_engine"
	kind "SharedLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs{
		"%{prj.name}/vendor/spdlog/include",
		"game_engine/src"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines{
			"GE_PLATFORM_WINDOWS",
			"GE_BUILD_DLL"
		}
		
		postbuildcommands{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
		
	filter "configurations:Debug"
		defines "GE_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "GE_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "GE_DIST"
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
		symbols "On"
		
	filter "configurations:Release"
		defines "GE_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "GE_DIST"
		optimize "On"
		
	filter "action:vs*"
		buildoptions { "/utf-8" }