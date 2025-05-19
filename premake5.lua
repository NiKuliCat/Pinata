workspace "PinataEngine"
    architecture "x86_64"
     startproject "Editor"   
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
IncludeDir["entt"] = "PinataEngine/vendor/entt/include"

group "Dependencies"
    include "PinataEngine/vendor/GLFW"
    include "PinataEngine/vendor/Glad"
    include "PinataEngine/vendor/ImGui"
group "" 

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
        "%{prj.name}/vendor/stb_image/**.h",
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
        "%{prj.name}/vendor/stb_image",
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.entt}"
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
        "PinataEngine/vendor",
        "%{IncludeDir.glm}",
         "%{IncludeDir.entt}"
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


project "Editor"
    location "Editor"
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
        "PinataEngine/vendor",
        "%{IncludeDir.glm}",
         "%{IncludeDir.entt}"
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