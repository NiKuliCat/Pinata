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
		virtual void Creat(const std::string& vertexPath, const std::string& fragmentPath ) { }

		virtual void Register(){}
		virtual void UnRegister(){}

		virtual void SetMat4(const std::string& name, const glm::mat4& matrix){}




	protected:
		uint32_t m_Program_ID;
	};


}