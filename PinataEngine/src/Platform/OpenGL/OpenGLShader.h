#pragma once
#include "Pinata/Renderer/Shader.h"

namespace Pinata {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(){}
		~OpenGLShader(){}

		virtual void Creat(const std::string& vertexPath = "", const std::string& fragmentPath = "") override;

		virtual void Register() override;
		virtual void UnRegister() override;

	private:
		uint32_t CompileShader(uint32_t type, const std::string& source);
	};

}
