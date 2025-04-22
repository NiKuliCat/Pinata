#include "ptapch.h"
#include "VertexArray.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
namespace Pinata {
	VertexArray* VertexArray::Create()
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
			return new OpenGLVertexArray();
			break;
		}
		}

		PTA_CORE_ERROR("UnKown RendererAPI !");
		return nullptr;
	}
}