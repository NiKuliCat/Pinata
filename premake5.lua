workspace "PinataEngine"
    architecture "x86_64"
     startproject "Editor"   
    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }
    flags                           --���ñ�����ѡ��
	{
		"MultiProcessorCompile"     --�ദ�������б���
	}
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/PinataEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/PinataEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/PinataEngine/vendor/ImGui"
IncludeDir["glm"] = "%{wks.location}/PinataEngine/vendor/glm"
IncludeDir["entt"] = "%{wks.location}/PinataEngine/vendor/entt/include"
IncludeDir["yaml_cpp"] = "%{wks.location}/PinataEngine/vendor/yaml-cpp/include"
IncludeDir["magic_enum"] = "%{wks.location}/PinataEngine/vendor/magic_enum/include"
group "Dependencies"
    include "PinataEngine/vendor/GLFW"
    include "PinataEngine/vendor/Glad"
    include "PinataEngine/vendor/ImGui"
    include "PinataEngine/vendor/yaml-cpp"
group "" 

include "PinataEngine"
include "Editor"
include "Sandbox"