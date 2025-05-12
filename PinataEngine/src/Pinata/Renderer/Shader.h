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
		static Ref<Shader> Creat(const std::string& filepath);
		static Ref<Shader> Creat(const std::string& vertexPath, const std::string& fragmentPath);

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual void SetInt(const std::string& name, const uint32_t value) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& matrix) = 0;
		virtual void SetFloat(const std::string& name, const float value) = 0;
		virtual void SetVector(const std::string& name, const glm::vec4& value) = 0;
		virtual void SetVector(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetVector(const std::string& name, const glm::vec2& value) = 0;
		virtual void SetColor(const std::string& name, const glm::vec4& color) = 0;
		virtual void SetColor(const std::string& name, const glm::vec3& color) = 0;

		virtual void SetIntArray(const std::string& name, const int* vaule,const uint32_t count) = 0;

		virtual const uint32_t GetID() const  = 0;
		virtual const std::string& GetName() const = 0;
	};




}