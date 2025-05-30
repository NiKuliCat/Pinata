#pragma once
#include "Pinata/Renderer/Material.h"

namespace Pinata {


	class OpenGLMaterial : public Material
	{
	public:
		OpenGLMaterial(const Ref<Texture2D>& texture);
		OpenGLMaterial(const uint32_t shaderID,const Ref<Texture2D>& texture);
		OpenGLMaterial(const uint32_t shaderID,const Ref<Texture2D>& texture,glm::vec4& color );
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

		virtual void SetColor(const glm::vec4& color) override;
	public:
		virtual const  uint32_t GetShaderID() const override { return m_ShaderID; }
		virtual const Ref<Texture2D> GetTexture() const override { return m_Texture; }
		virtual const glm::vec4& GetColor() const override { return m_VertexColor; }
		virtual  glm::vec4& GetColor()  override { return m_VertexColor; }
	private:
		uint32_t m_ShaderID = -1;
		Ref<Shader> m_Shader;
		Ref<Texture2D> m_Texture;
		glm::vec4 m_VertexColor = glm::vec4(1.0f);
	};

}