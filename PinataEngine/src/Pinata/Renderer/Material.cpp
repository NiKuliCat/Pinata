#include "ptapch.h"
#include "Material.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLMaterial.h"
namespace Pinata {




	Ref<Material> Material::Create(const uint32_t shaderID,const  glm::mat4& model)
	{
		switch (Renderer::GetAPI())
		{
			case  RendererAPI::API::None:
			{
				return nullptr;
				break;
			}
			case  RendererAPI::API::OpenGL:
			{
				return CreateRef<OpenGLMaterial>(shaderID, model);
				break;
			}
		}
	}

}