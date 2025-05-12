#include "ptapch.h"
#include "OpenGLShader.h"
#include "GLSLShaderHelper.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
namespace Pinata {

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		std::unordered_map<GLenum, std::string> src = GLSLShaderHelper::Read(filepath);

		uint32_t program = glCreateProgram();
		uint32_t vs = CompileShader(GL_VERTEX_SHADER, src[GL_VERTEX_SHADER]);
		uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, src[GL_FRAGMENT_SHADER]);

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);
		m_Program_ID = program;
	}

	OpenGLShader::OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath)
	{
		std::string vertexSrc_ = GLSLShaderHelper::Read(vertexPath, ShaderType::Vertex);
		std::string fragmentSrc_ = GLSLShaderHelper::Read(fragmentPath, ShaderType::Fragment);
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
	void OpenGLShader::Bind()
	{
		glUseProgram(m_Program_ID);
	}

	void OpenGLShader::UnBind()
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, const uint32_t value)
	{
		GLint location = glGetUniformLocation(m_Program_ID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_Program_ID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
		//glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::SetFloat(const std::string& name, const float value)
	{
		GLint location = glGetUniformLocation(m_Program_ID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::SetVector(const std::string& name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(m_Program_ID, name.c_str());
		glUniform4f(location, value.x,value.y,value.z,value.w);
	}

	void OpenGLShader::SetVector(const std::string& name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(m_Program_ID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::SetVector(const std::string& name, const glm::vec2& value)
	{
		GLint location = glGetUniformLocation(m_Program_ID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::SetColor(const std::string& name, const glm::vec4& color)
	{
		OpenGLShader::SetVector(name, color);
	}

	void OpenGLShader::SetColor(const std::string& name, const glm::vec3& color)
	{
		OpenGLShader::SetVector(name, color);
	}

	void OpenGLShader::SetIntArray(const std::string& name, const int* vaule, const uint32_t count)
	{
		GLint location = glGetUniformLocation(m_Program_ID, name.c_str());
		glUniform1iv(location, count, vaule);
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

			PTA_CORE_ERROR("{0} shader is failed to compile", type == GL_VERTEX_SHADER ? "vertex" : "fragment");
			PTA_CORE_ERROR("{0}", log);

			glDeleteShader(id);
			return 0;
		}

		return id;
	}

}