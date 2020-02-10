workspace "Dimon"
    architecture "x64"
    startproject "DimonGame"
	--startproject "DimonGame"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
	--flags
	--{
	--	"MultiProcessorCompile"
	--}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Dimon/vendor/GLFW/include"
IncludeDir["GLAD"] = "Dimon/vendor/GLAD/include"
--IncludeDir["ImGui"] = "Dimon/vendor/imgui"
--IncludeDir["glm"] = "Dimon/vendor/glm"
--IncludeDir["stb_image"] = "Dimon/vendor/stb_image"

group "Dependencies"
	include "Dimon/vendor/GLFW"
	include "Dimon/vendor/GLAD"
	--include "Dimon/vendor/imgui"

group ""

project "Dimon"
	location "Dimon"
	kind "SharedLib"
	language "C++"
	--cppdialect "C++17"
	--staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "dmpch.h"
	pchsource "Dimon/src/dmpch.cpp"
    
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		--"%{prj.name}/vendor/stb_image/**.h",
		--"%{prj.name}/vendor/stb_image/**.cpp",
		--"%{prj.name}/vendor/glm/glm/**.hpp",
		--"%{prj.name}/vendor/glm/glm/**.inl",
	}

	--defines
	--{
	--	"_CRT_SECURE_NO_WARNINGS"
	--}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}"
		--"%{IncludeDir.ImGui}",
		--"%{IncludeDir.glm}",
		--"%{IncludeDir.stb_image}"
	}

	links 
	{ 
		"GLFW",
		"GLAD",
		--"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"
		defines
		{
            "DM_PLATFORM_WINDOWS",
			"DM_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
        }
		
        
	filter "configurations:Debug"
		defines "DM_DEBUG"
		buildoptions "/MDd"
		symbols "on"

	filter "configurations:Release"
		defines "DM_RELEASE"
		buildoptions "/MD"
		optimize "on"

	filter "configurations:Dist"
		defines "DM_DIST"
		buildoptions "/MD"
		optimize "on"

project "DimonGame"
	location "DimonGame"
	kind "ConsoleApp"
	language "C++"
	--cppdialect "C++17"
	--staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Dimon/vendor/spdlog/include",
		"Dimon/src",
        "Dimon/vendor"
        --,"%{IncludeDir.glm}"
	}

	links
	{
		"Dimon"
	}

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
		systemversion "latest"
		--postbuildcommands { "{COPY} %{cfg.buildtarget.relpaht} ../bin/" .. outputdir .. "/DemonGame" }
		defines
		{
            "DM_PLATFORM_WINDOWS"
		}
	filter "configurations:Debug"
		defines "DM_DEBUG"
		buildoptions "/MDd"
		symbols "on"

	filter "configurations:Release"
		defines "DM_RELEASE"
		buildoptions "/MD"
		optimize "on"

	filter "configurations:Dist"
		defines "DM_DIST"
		buildoptions "/MD"
		optimize "on"