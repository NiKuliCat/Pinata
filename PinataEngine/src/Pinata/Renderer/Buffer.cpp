#include "ptapch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
namespace Pinata {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:
			{
				return nullptr;
				break;
			}
			case RendererAPI::OpenGL:
			{
				return  new  OpenGLVertexBuffer(vertices, size);
				break;
			}
		}

		PTA_CORE_ERROR("UnKown RendererAPI !");
		return nullptr;
	}


	///////////////////////////// index buffer /////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
		{
			return nullptr;
			break;
		}
		case RendererAPI::OpenGL:
		{
			return  new  OpenGLIndexBuffer(indices, count);
			break;
		}
		}

		PTA_CORE_ERROR("UnKown RendererAPI !");
		return nullptr;
	}
}