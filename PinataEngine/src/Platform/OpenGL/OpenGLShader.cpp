#include "ptapch.h"
#include "OpenGLShader.h"
#include "GLSLShaderHelper.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
namespace Pinata {

	void OpenGLShader::Creat(const std::string& vertexPath, const std::string& fragmentPath)
	{
		std::string vertexSrc_ = GLSLShaderHelper::Read(vertexPath, ShaderType::Vertex);
		std::string fragmentSrc_ = GLSLShaderHelper::Read(fragmentPath, ShaderType::Fragment);
		PTA_CORE_INFO("vertexShader:{0}", fragmentSrc_);
		uint32_t program = glCreateProgram();
		uint32_t vs = CompileShader(GL_VERTEX_SHADER, vertexSrc_);
		uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc_);

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);
		m_Program_ID = program;
	}

	void OpenGLShader::Register()
	{
		glUseProgram(m_Program_ID);
	}

	void OpenGLShader::UnRegister()
	{
		glUseProgram(0);
	}

	uint32_t OpenGLShader::CompileShader(uint32_t type, const std::string& source)
	{
		uint32_t id = glCreateShader(type);
		const char* shaderSrc = source.c_str();
		glShaderSource(id, 1, &shaderSrc, nullptr);
		glCompileShader(id);
		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);


		if (result == GL_FALSE)
		{
			int len;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
			char* log = (char*)malloc(len * sizeof(char));
			glGetShaderInfoLog(id, len, &len, log);
			std::cout << "[" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader failed to compile] " << std::endl;
			std::cout << log << std::endl;
			std::cout << "" << std::endl;
			glDeleteShader(id);
			return 0;
		}

		return id;
	}

}