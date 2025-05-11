#include "ptapch.h"
#include "OpenGLMaterial.h"
#include "Pinata/Renderer/ShaderLibrary.h"
namespace Pinata {
	OpenGLMaterial::OpenGLMaterial(const uint32_t shaderID,const glm::mat4& model)
		:m_ShaderID(shaderID),m_ModelMatrix(model),m_Shader(ShaderLibrary::Get(shaderID))
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

}