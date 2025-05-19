#pragma once
#include "Pinata/Renderer/Material.h"

namespace Pinata {


	class OpenGLMaterial : public Material
	{
	public:
		OpenGLMaterial(const uint32_t shaderID,const Ref<Texture2D>& texture);
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
		virtual const Ref<Texture2D> GetTexture() const override { return m_Texture; }
	private:
		uint32_t m_ShaderID = -1;
		Ref<Shader> m_Shader;
		Ref<Texture2D> m_Texture;
	};

}