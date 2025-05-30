project "Editor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" ..outputdir.. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" ..outputdir.. "/%{prj.name}")

    files
    {
        "src/**.h",
        "src/**.cpp",
    }

    includedirs
    {
        "%{wks.location}/PinataEngine/vendor/spdlog/include",
        "%{wks.location}/PinataEngine/src",
        "%{wks.location}/PinataEngine/vendor",
        "%{IncludeDir.glm}",
        "%{IncludeDir.entt}",
        "%{IncludeDir.yaml_cpp}",
        "%{IncludeDir.magic_enum}",
        "%{IncludeDir.ImGuizmo}"
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