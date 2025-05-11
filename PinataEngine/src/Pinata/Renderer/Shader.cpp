#include "ptapch.h"

#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
namespace Pinata {



	Ref<Shader> Shader::Creat(const std::string& filepath)
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
			return CreateRef<OpenGLShader>(filepath);
			break;
		}
		}
	}

	Ref<Shader> Shader::Creat(const std::string& vertexPath, const std::string& fragmentPath)
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
				return CreateRef<OpenGLShader>(vertexPath,fragmentPath);
				break;
			}
		}
	}

}