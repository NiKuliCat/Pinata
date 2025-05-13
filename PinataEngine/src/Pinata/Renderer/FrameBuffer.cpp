#include "ptapch.h"
#include "FrameBuffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLFrameBuffer.h"
namespace Pinata {




	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferDescription& description)
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
			return CreateRef<OpenGLFrameBuffer>(description);
			break;
		}
		}

		PTA_CORE_ERROR("UnKown RendererAPI !");
		return nullptr;
	}

}