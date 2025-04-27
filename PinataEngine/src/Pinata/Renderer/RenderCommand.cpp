#include "ptapch.h"
#include "RenderCommand.h"	
#include "Platform/OpenGL/OpenGLRendererAPI.h"
namespace Pinata {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}