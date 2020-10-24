workspace "Dimon"
    architecture "x64"
    startproject "DimonGame"

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
IncludeDir["Vulkan"] = "Dimon/vendor/Vulkan/Include"
IncludeDir["VulkanLib"] = "Dimon/vendor/Vulkan/Lib"
IncludeDir["ImGui"] = "Dimon/vendor/ImGui"
IncludeDir["glm"] = "Dimon/vendor/glm"
IncludeDir["stb_image"] = "Dimon/vendor/stb_image"

group "Dependencies"
	include "Dimon/vendor/GLFW"
	include "Dimon/vendor/GLAD"
	include "Dimon/vendor/ImGui"

group ""

project "Dimon"
	location "Dimon"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "dmpch.h"
	pchsource "Dimon/src/dmpch.cpp"
    
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	--defines
	--{
	--	"IMGUI_API=__declspec(dllexport)"
	--	"_CRT_SECURE_NO_WARNINGS"
	--}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.Vulkan}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}
	libdirs {
		"%{IncludeDir.VulkanLib}"
	}
	defines
		{
			"_CRT_SECURE_NO_WARNINGS"
        }
	links 
	{ 
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib",
		"vulkan-1.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
        systemversion "latest"
		defines
		{
            "DM_PLATFORM_WINDOWS",
			"DM_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"_CRT_SECURE_NO_WARNINGS"
        }
		--postbuildcommands { ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/DimonGame") }
		--postbuildcommands { ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/DimonGame/\"") }
        
	filter "configurations:Debug"
		defines "DM_DEBUG"
		runtime "debug"
		symbols "on"

	filter "configurations:Release"
		defines "DM_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "DM_DIST"
		runtime "Release"
		optimize "on"

project "DimonGame"
	location "DimonGame"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
        "Dimon/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Dimon"
	}
	
    filter "system:windows"
        cppdialect "C++17"
		systemversion "latest"
		defines
		{
            "DM_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "DM_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "DM_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "DM_DIST"
		runtime "Release"
		optimize "on"

project "flappybird"
	location "flappybird"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
        "Dimon/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Dimon"
	}
	
    filter "system:windows"
        cppdialect "C++17"
		systemversion "latest"
		defines
		{
            "DM_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "DM_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "DM_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "DM_DIST"
		runtime "Release"
		optimize "on"

project "DimonEditor"
	location "DimonEditor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
        "Dimon/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Dimon"
	}

    filter "system:windows"
        cppdialect "C++17"
		systemversion "latest"
		defines
		{
            "DM_PLATFORM_WINDOWS"
		}
	filter "configurations:Debug"
		defines "DM_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "DM_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "DM_DIST"
		runtime "Release"
		optimize "on"