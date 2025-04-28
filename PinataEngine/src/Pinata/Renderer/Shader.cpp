#include "ptapch.h"

#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
namespace Pinata {



	Shader* Shader::Creat(const std::string& vertexPath, const std::string& fragmentPath)
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
				return new OpenGLShader(vertexPath,fragmentPath);
				break;
			}
		}
	}

}