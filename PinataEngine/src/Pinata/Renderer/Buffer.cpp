#include "ptapch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
namespace Pinata {

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			{
				return nullptr;
				break;
			}
			case  RendererAPI::API::OpenGL:
			{
				return  std::make_shared<OpenGLVertexBuffer>(vertices, size);
				break;
			}
		}

		PTA_CORE_ERROR("UnKown RendererAPI !");
		return nullptr;
	}


	///////////////////////////// index buffer /////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
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
			return  std::make_shared<OpenGLIndexBuffer>(indices, count);
			break;
		}
		}

		PTA_CORE_ERROR("UnKown RendererAPI !");
		return nullptr;
	}
}