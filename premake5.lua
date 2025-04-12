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
    kind "SharedLib"
    language "C++"

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
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"
        defines
        {
            "PINATA_PLATFORM_WINDOW",
            "PINATA_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..outputdir.. "/Sandbox")
        }

    filter "system:Debug"
        defines "PTA_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "system:Release"
        defines "PTA_RELEASE"
        buildoptions "/MD"
        symbols "On"

    filter "system:Dist"
        defines "PTA_DIST"
        buildoptions "/MD"
        symbols "On"


project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

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
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"
        defines
        {
            "PINATA_PLATFORM_WINDOW"
        }

    filter "system:Debug"
        defines "PTA_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "system:Release"
        defines "PTA_RELEASE"
        buildoptions "/MD"
        symbols "On"

    filter "system:Dist"
        defines "PTA_DIST"
        buildoptions "/MD"
        symbols "On"