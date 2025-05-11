#pragma once
#include "Pinata/Renderer/Material.h"

namespace Pinata {


	class OpenGLMaterial : public Material
	{
	public:
		OpenGLMaterial(const uint32_t shaderID,const glm::mat4& model);
		~OpenGLMaterial();


		virtual void Set(const std::string& name, int value) override;
		virtual void Set(const std::string& name, float value) override;
		virtual void Set(const std::string& name, const uint32_t value) override;
		virtual void Set(const std::string& name, const glm::vec2& value) override;
		virtual void Set(const std::string& name, const glm::vec3& value) override;
		virtual void Set(const std::string& name, const glm::vec4& value) override;
		virtual void Set(const std::string& name, const glm::mat3& value) override;
		virtual void Set(const std::string& name, const glm::mat4& value) override;
		virtual void Set(const std::string& name, const Ref<Texture2D>& value) override;


	public:
		virtual const  uint32_t GetShaderID() const override { return m_ShaderID; }
		virtual const  glm::mat4& GetModelMatrix() const { return  m_ModelMatrix; }

	private:
		uint32_t m_ShaderID;
		Ref<Shader> m_Shader;
		glm::mat4 m_ModelMatrix;
	};

}