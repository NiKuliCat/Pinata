#include "ptapch.h"
#include "OpenGLMaterial.h"
#include "Pinata/Renderer/ShaderLibrary.h"
namespace Pinata {
	OpenGLMaterial::OpenGLMaterial(const Ref<Texture2D>& texture)
		:m_Texture(texture), m_VertexColor(glm::vec4(1.0f))
	{
	}
	OpenGLMaterial::OpenGLMaterial(const uint32_t shaderID, const Ref<Texture2D>& texture)
		:m_ShaderID(shaderID),m_Shader(ShaderLibrary::Get(shaderID)),m_Texture(texture),m_VertexColor(glm::vec4(1.0f))
	{
	}

	OpenGLMaterial::OpenGLMaterial(const uint32_t shaderID, const Ref<Texture2D>& texture, glm::vec4& color)
		:m_ShaderID(shaderID), m_Shader(ShaderLibrary::Get(shaderID)), m_Texture(texture),m_VertexColor(color)
	{
	}

	OpenGLMaterial::~OpenGLMaterial()
	{
	}

	void OpenGLMaterial::Set(const std::string& name, int value)
	{
		m_Shader->SetInt(name, value);
	}

	void OpenGLMaterial::Set(const std::string& name, float value)
	{
		m_Shader->SetFloat(name, value);
	}

	void OpenGLMaterial::Set(const std::string& name, const uint32_t value)
	{
		m_Shader->SetInt(name, value);
	}

	void OpenGLMaterial::Set(const std::string& name, const glm::vec2& value)
	{
		m_Shader->SetVector(name, value);
	}

	void OpenGLMaterial::Set(const std::string& name, const glm::vec3& value)
	{
		m_Shader->SetVector(name, value);
	}

	void OpenGLMaterial::Set(const std::string& name, const glm::vec4& value)
	{
		m_Shader->SetVector(name, value);
	}

	void OpenGLMaterial::Set(const std::string& name, const glm::mat3& value)
	{
	}

	void OpenGLMaterial::Set(const std::string& name, const glm::mat4& value)
	{
		m_Shader->SetMat4(name, value);
	}

	void OpenGLMaterial::Set(const std::string& name, const Ref<Texture2D>& value)
	{
	}

	void OpenGLMaterial::SetColor(const glm::vec4& color)
	{
		m_VertexColor = color;
	}

}