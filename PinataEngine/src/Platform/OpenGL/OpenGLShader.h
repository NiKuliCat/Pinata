#pragma once
#include "Pinata/Renderer/Shader.h"

namespace Pinata {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader::OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath);
		~OpenGLShader(){}

		virtual void Bind() override;
		virtual void UnBind() override;

	public:
		virtual void SetInt(const std::string& name, const uint32_t value) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& matrix) override;
		virtual void SetFloat(const std::string& name, const float value) override;

		virtual void SetVector(const std::string& name, const glm::vec4& value) override;
		virtual void SetVector(const std::string& name, const glm::vec3& value) override;
		virtual void SetVector(const std::string& name, const glm::vec2& value) override;
		virtual void SetColor(const std::string& name, const glm::vec4& color) override;
		virtual void SetColor(const std::string& name, const glm::vec3& color) override;

		virtual void SetIntArray(const std::string& name, const int* vaule, const uint32_t count) override;

		virtual const uint32_t GetID() const override { return m_Program_ID; }
		virtual const std::string& GetName() const override { return m_Name; }
	private:
		uint32_t CompileShader(uint32_t type, const std::string& source);


	private:
		uint32_t m_Program_ID;
		std::string  m_Name;

	};

}
