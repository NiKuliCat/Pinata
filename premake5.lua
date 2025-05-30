include "Dependencies.lua"

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

group "Dependencies"
    include "PinataEngine/vendor/GLFW"
    include "PinataEngine/vendor/Glad"
    include "PinataEngine/vendor/ImGui"
    include "PinataEngine/vendor/yaml-cpp"
group "" 

include "PinataEngine"
include "Editor"
include "Sandbox"