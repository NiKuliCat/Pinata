project "PinataEngine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" ..outputdir.. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" ..outputdir.. "/%{prj.name}")

    pchheader "ptapch.h"
    pchsource "src/ptapch.cpp"

    files
    {
        "src/**.h",
        "src/**.cpp",
        "vendor/stb_image/**.h",
        "vendor/glm/glm/**.hpp",
        "vendor/glm/glm/**.inl"
    }
    defines
    {
        "_CRT_SECURE_NO_WARNINGS",
        "GLFW_INCLUDE_NONE"
    }

    includedirs
    {
        "src",
        "vendor/spdlog/include",
        "vendor/stb_image",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.entt}",
        "%{IncludeDir.yaml_cpp}"
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
        "opengl32.lib",
        "yaml-cpp"
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