#pragma once
#include "Shader.h"
#include "Texture.h"
namespace Pinata {
	class Material
	{
	public:
		virtual void Set(const std::string& name, int value) = 0;
		virtual void Set(const std::string& name, float value) = 0;
		virtual void Set(const std::string& name, const uint32_t value) = 0;
		virtual void Set(const std::string& name, const glm::vec2& value) = 0;
		virtual void Set(const std::string& name, const glm::vec3& value) = 0;
		virtual void Set(const std::string& name, const glm::vec4& value) = 0;
		virtual void Set(const std::string& name, const glm::mat3& value) = 0;
		virtual void Set(const std::string& name, const glm::mat4& value) = 0;
		virtual void Set(const std::string& name, const Ref<Texture2D>& value) = 0;

	public:

		virtual const  uint32_t GetShaderID() const = 0;
		virtual const  glm::mat4& GetModelMatrix() const = 0;

	public:
		static Ref<Material> Create(const uint32_t shaderID,const  glm::mat4& model);

	};
}