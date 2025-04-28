#pragma once
#include "Pinata/Renderer/Shader.h"

namespace Pinata {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath);
		~OpenGLShader(){}

		virtual void Register() override;
		virtual void UnRegister() override;

	public:
		virtual void SetMat4(const std::string& name, const glm::mat4& matrix) override;
		virtual void SetFloat(const std::string& name, const float value) override;

		virtual void SetVector(const std::string& name, const glm::vec4& value) override;
		virtual void SetVector(const std::string& name, const glm::vec3& value) override;
		virtual void SetVector(const std::string& name, const glm::vec2& value) override;
		virtual void SetColor(const std::string& name, const glm::vec4& color) override;
		virtual void SetColor(const std::string& name, const glm::vec3& color) override;
	private:
		uint32_t CompileShader(uint32_t type, const std::string& source);
	};

}
