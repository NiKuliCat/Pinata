#include "ptapch.h"
#include "OpenGLShader.h"
#include "GLSLShaderHelper.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <shaderc/shaderc.hpp>
#include <spirv_cross/spirv_cross.hpp>
#include <spirv_cross/spirv_glsl.hpp>
#include "OpenGLUtils.h"
namespace Pinata {

	OpenGLShader::OpenGLShader(const std::string& filepath)
		:m_Filepath(filepath)
	{
		auto src = GLSLShaderHelper::Read(filepath);

		//创建着色器缓存文件
		OpenGLUtils::CreateCacheDirectoryIfNeeded();
		//将glsl src 编译成 中间件 spirv
		CompileOrGetVulkanBinaries(src);
		CompileOrGetOpenGLBinaries();
		CreateProgram();


		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind('.');
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		m_Name = filepath.substr(lastSlash, count);

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

	void OpenGLShader::CompileOrGetVulkanBinaries(const std::unordered_map<GLenum, std::string>& shaderSource)
	{
		GLuint program = glCreateProgram();

		shaderc::Compiler compiler;
		shaderc::CompileOptions options;
		options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_3);
		const bool optimize = true;
		if (optimize)
		{
			options.SetOptimizationLevel(shaderc_optimization_level_performance);
		}

		std::filesystem::path cacheDir = OpenGLUtils::GetCacheDirectory();

		auto& shaderData = m_Vulkan_SPIRV;
		shaderData.clear();

		for (auto&& [stage, source] : shaderSource)
		{
			std::filesystem::path shaderFilePath = m_Filepath;
			std::filesystem::path cachedPath = cacheDir / (shaderFilePath.filename().string() + OpenGLUtils::GLShaderStageCachedVulkanFileExtension(stage));

			std::ifstream in(cachedPath, std::ios::in | std::ios::binary);
			if (in.is_open())
			{
				in.seekg(0, std::ios::end);
				auto size = in.tellg();
				in.seekg(0, std::ios::beg);

				auto& data = shaderData[stage];
				data.resize(size / sizeof(uint32_t));
				in.read((char*)data.data(), size);
			}

			else
			{
				shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(source, OpenGLUtils::GLShaderStageToShaderC(stage), m_Filepath.c_str(), options);
				if (module.GetCompilationStatus() != shaderc_compilation_status_success)
				{
					PTA_CORE_ERROR(module.GetErrorMessage());
					PTA_CORE_ASSERT(false);
				}

				shaderData[stage] = std::vector<uint32_t>(module.cbegin(), module.cend());

				std::ofstream out(cachedPath, std::ios::out | std::ios::binary);
				if (out.is_open())
				{
					auto& data = shaderData[stage];
					out.write((char*)data.data(), data.size() * sizeof(uint32_t));
					out.flush();
					out.close();
				}
			}

		}
		for (auto&& [stage, data] : shaderData)
			Reflect(stage, data);
	}

	void OpenGLShader::CompileOrGetOpenGLBinaries()
	{
		auto& shaderData = m_OpenGL_SPIRV;

		shaderc::Compiler compiler;
		shaderc::CompileOptions options;
		options.SetTargetEnvironment(shaderc_target_env_opengl, shaderc_env_version_opengl_4_5);
		const bool optimize = false;
		if (optimize)
			options.SetOptimizationLevel(shaderc_optimization_level_performance);

		std::filesystem::path cacheDirectory = OpenGLUtils::GetCacheDirectory();

		shaderData.clear();
		m_OpenGL_SourceCode.clear();
		for (auto&& [stage, spirv] : m_Vulkan_SPIRV)
		{
			std::filesystem::path shaderFilePath = m_Filepath;
			std::filesystem::path cachedPath = cacheDirectory / (shaderFilePath.filename().string() + OpenGLUtils::GLShaderStageCachedOpenGLFileExtension(stage));

			std::ifstream in(cachedPath, std::ios::in | std::ios::binary);
			if (in.is_open())
			{
				in.seekg(0, std::ios::end);
				auto size = in.tellg();
				in.seekg(0, std::ios::beg);

				auto& data = shaderData[stage];
				data.resize(size / sizeof(uint32_t));
				in.read((char*)data.data(), size);
			}
			else
			{
				spirv_cross::CompilerGLSL glslCompiler(spirv);
				m_OpenGL_SourceCode[stage] = glslCompiler.compile();
				auto& source = m_OpenGL_SourceCode[stage];

				shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(source, OpenGLUtils::GLShaderStageToShaderC(stage), m_Filepath.c_str());
				if (module.GetCompilationStatus() != shaderc_compilation_status_success)
				{
					PTA_CORE_ERROR(module.GetErrorMessage());
					PTA_CORE_ASSERT(false);
				}

				shaderData[stage] = std::vector<uint32_t>(module.cbegin(), module.cend());

				std::ofstream out(cachedPath, std::ios::out | std::ios::binary);
				if (out.is_open())
				{
					auto& data = shaderData[stage];
					out.write((char*)data.data(), data.size() * sizeof(uint32_t));
					out.flush();
					out.close();
				}
			}
		}
	}

	void OpenGLShader::CreateProgram()
	{
		GLuint program = glCreateProgram();

		std::vector<GLuint> shaderIDs;
		for (auto&& [stage, spirv] : m_OpenGL_SPIRV)
		{
			GLuint shaderID = shaderIDs.emplace_back(glCreateShader(stage));
			glShaderBinary(1, &shaderID, GL_SHADER_BINARY_FORMAT_SPIR_V, spirv.data(), spirv.size() * sizeof(uint32_t)); // ?
			glSpecializeShader(shaderID, "main", 0, nullptr, nullptr);
			glAttachShader(program, shaderID);
		}

		//尝试链接
		glLinkProgram(program);
		GLint isLinked;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, infoLog.data());
			PTA_CORE_ERROR("Shader linking failed ({0}):\n{1}", m_Filepath, infoLog.data());

			glDeleteProgram(program);

			for (auto id : shaderIDs)
				glDeleteShader(id);
		}

		for (auto id : shaderIDs)
		{
			glDetachShader(program, id);
			glDeleteShader(id);
		}

		m_Program_ID = program;
	}

	void OpenGLShader::Reflect(GLenum stage, const std::vector<uint32_t>& shaderData)
	{
		spirv_cross::Compiler compiler(shaderData);
		spirv_cross::ShaderResources resources = compiler.get_shader_resources();

		PTA_CORE_TRACE("OpenGLShader::Reflect - {0} {1}", OpenGLUtils::GLShaderStageToString(stage), m_Filepath);
		PTA_CORE_TRACE("    {0} uniform buffers", resources.uniform_buffers.size());
		PTA_CORE_TRACE("    {0} resources", resources.sampled_images.size());

		PTA_CORE_TRACE("Uniform buffers:");
		for (const auto& resource : resources.uniform_buffers)
		{
			const auto& bufferType = compiler.get_type(resource.base_type_id);
			uint32_t bufferSize = compiler.get_declared_struct_size(bufferType);
			uint32_t binding = compiler.get_decoration(resource.id, spv::DecorationBinding);
			int memberCount = bufferType.member_types.size();

			PTA_CORE_TRACE("  {0}", resource.name);
			PTA_CORE_TRACE("    Size = {0}", bufferSize);
			PTA_CORE_TRACE("    Binding = {0}", binding);
			PTA_CORE_TRACE("    Members = {0}", memberCount);
		}
	}

}