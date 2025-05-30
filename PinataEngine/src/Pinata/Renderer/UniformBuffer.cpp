#include "ptapch.h"
#include "UniformBuffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLUniformBuffer.h"
namespace Pinata {



	Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
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
				return CreateRef<OpenGLUniformBuffer>(size,binding);
				break;
			}
		}

		PTA_CORE_ERROR("UnKown RendererAPI !");
		return nullptr;
	}

}