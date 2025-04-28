#pragma once
#include <string>
#include <glm/glm.hpp>
namespace Pinata {

	enum ShaderType
	{
		Vertex,
		Fragment
	};

	class Shader
	{
	public:
		static Shader* Creat(const std::string& vertexPath, const std::string& fragmentPath);

		virtual void Register(){}
		virtual void UnRegister(){}

		virtual void SetMat4(const std::string& name, const glm::mat4& matrix){}
		virtual void SetFloat(const std::string& name, const float value){}
		virtual void SetVector(const std::string& name, const glm::vec4& value){}
		virtual void SetVector(const std::string& name, const glm::vec3& value){}
		virtual void SetVector(const std::string& name, const glm::vec2& value){}
		virtual void SetColor(const std::string& name, const glm::vec4& color) {}
		virtual void SetColor(const std::string& name, const glm::vec3& color) {}
	protected:
		uint32_t m_Program_ID;
	};


}