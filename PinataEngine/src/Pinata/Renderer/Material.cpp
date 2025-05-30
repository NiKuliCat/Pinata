#include "ptapch.h"
#include "Material.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLMaterial.h"
namespace Pinata {




	Ref<Material> Material::Create(const Ref<Texture2D>& texture)
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
			return CreateRef<OpenGLMaterial>(texture);
			break;
		}
		}
	}

	Ref<Material> Material::Create(const uint32_t shaderID, const Ref<Texture2D>& texture)
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
				return CreateRef<OpenGLMaterial>(shaderID, texture);
				break;
			}
		}
	}

}