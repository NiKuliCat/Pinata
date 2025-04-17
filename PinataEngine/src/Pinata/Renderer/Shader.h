#pragma once
#include <string>
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

	protected:
		uint32_t m_Program_ID;
	};


}