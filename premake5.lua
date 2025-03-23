workspace "PinataEngine"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
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
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/src"
    }
    buildoptions
    {
        "/utf-8"
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
        symbols "On"

    filter "system:Release"
        defines "PTA_RELEASE"
        symbols "On"

    filter "system:Dist"
        defines "PTA_DIST"
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
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "PinataEngine/vendor/spdlog/include",
        "PinataEngine/src"
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
        symbols "On"

    filter "system:Release"
        defines "PTA_RELEASE"
        symbols "On"

    filter "system:Dist"
        defines "PTA_DIST"
        symbols "On"