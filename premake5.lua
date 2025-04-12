workspace "PinataEngine"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "PinataEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "PinataEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "PinataEngine/vendor/ImGui"
IncludeDir["glm"] = "PinataEngine/vendor/glm"

include "PinataEngine/vendor/GLFW"
include "PinataEngine/vendor/Glad"
include "PinataEngine/vendor/ImGui"


project "PinataEngine"
    location "PinataEngine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" ..outputdir.. "/%{prj.name}")
    objdir ("bin-int/" ..outputdir.. "/%{prj.name}")

    pchheader "ptapch.h"
    pchsource "Pinata/src/ptapch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }
    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }
    buildoptions
    {
        "/utf-8"
    }
    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"
        defines
        {
            "PINATA_PLATFORM_WINDOW",
            "PINATA_BUILD_DLL"
        }

    filter "configurations:Debug"
        defines "PTA_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "PTA_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "PTA_DIST"
        runtime "Release"
        optimize "On"


project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" ..outputdir.. "/%{prj.name}")
    objdir ("bin-int/" ..outputdir.. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "PinataEngine/vendor/spdlog/include",
        "PinataEngine/src",
        "PinataEngine/vendor/ImGui",
        "%{IncludeDir.glm}"
    }

    buildoptions
    {
        "/utf-8"
    }

    links
    {
        "PinataEngine"
    }

    filter "system:windows"
        systemversion "latest"
        defines
        {
            "PINATA_PLATFORM_WINDOW"
        }

    filter "configurations:Debug"
        defines "PTA_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "PTA_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "PTA_DIST"
        runtime "Release"
        optimize "On"