#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include "Pinata/Renderer/Shader.h"
namespace Pinata {

	class GLSLShaderHelper
	{
	public:
		static std::string Read(const std::string& filepath, const ShaderType type)
		{
			std::ifstream file(filepath);
			std::string line;
			std::stringstream result;
			bool enableRead = false;
			while (std::getline(file, line))
			{
				if ((line.find("#vertex") != std::string::npos && type == ShaderType::Vertex)
					|| (line.find("#fragment") != std::string::npos && type == ShaderType::Fragment))
				{
					enableRead = true;
					continue;
				}
				else if ((line.find("#vertex") != std::string::npos && type != ShaderType::Vertex)
					|| (line.find("#fragment") != std::string::npos && type != ShaderType::Fragment))
				{
					enableRead = false;
				}

				if (enableRead)
				{
					result << line << '\n';
				}

			}
			return result.str();
		}

	};

}