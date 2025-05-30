
VULKANSDK = os.getenv("VULKAN_SDK")


IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/PinataEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/PinataEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/PinataEngine/vendor/ImGui"
IncludeDir["glm"] = "%{wks.location}/PinataEngine/vendor/glm"
IncludeDir["entt"] = "%{wks.location}/PinataEngine/vendor/entt/include"
IncludeDir["yaml_cpp"] = "%{wks.location}/PinataEngine/vendor/yaml-cpp/include"
IncludeDir["magic_enum"] = "%{wks.location}/PinataEngine/vendor/magic_enum/include"
IncludeDir["ImGuizmo"] = "%{wks.location}/PinataEngine/vendor/ImGuizmo"
IncludeDir["VulkanSDK"] = "%{VULKANSDK}/Include"


LibraryDir = {}

LibraryDir["VulkanSDK"] = "%{VULKANSDK}/Lib"


Library = {}
Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["VulkanUtils"] = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"

Library["ShaderC_Debug"] = "%{LibraryDir.VulkanSDK}/shaderc_sharedd.lib"
Library["SPIRV_Cross_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-cored.lib"
Library["SPIRV_Cross_GLSL_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsld.lib"
Library["SPIRV_Tools_Debug"] = "%{LibraryDir.VulkanSDK}/SPIRV-Toolsd.lib"

Library["ShaderC_Release"] = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
Library["SPIRV_Cross_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"

