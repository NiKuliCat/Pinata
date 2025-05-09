#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include "Pinata/Renderer/Shader.h"
#include <glad/glad.h>
namespace Pinata {

	class GLSLShaderHelper
	{
	public:
		static std::unordered_map<GLenum, std::string> Read(const std::string& filepath)
		{
			std::unordered_map<GLenum, std::string> result; 
			std::ifstream file(filepath);
			std::string line;
			std::stringstream vertex;
			std::stringstream fragment;
			std::string target = "#program";
			bool reading = false;
			ShaderType curProcessType = ShaderType::Vertex;
			while (std::getline(file, line))
			{
				//����ע��
				size_t commentPos = line.find("//");
				if (commentPos != std::string::npos) {
					line = line.substr(0, commentPos);
				}
				//���жϸ����Ƿ�Ϊ��ǩ��
				//������β��λ
				std::string trimLine = Trim(line);
				if (trimLine.empty()) continue;

				//Ѱ�ұ�ǩֵ
				if (trimLine.find(target)== 0)
				{
					std::string subLine = trimLine.substr(target.length());
					subLine = Trim(subLine);
					if (subLine =="vertex")
					{
						curProcessType = ShaderType::Vertex;
						reading = true;
						continue;
					}
					else if (subLine == "fragment")
					{
						curProcessType = ShaderType::Fragment;
						reading = true;
						continue;
					}
				}
				//����ɹ������˶�ȡ�׶�
				if (reading)
				{
					switch (curProcessType)
					{
						case Pinata::Vertex:
						{
							vertex  << line << '\n';
							break;
						}
						case Pinata::Fragment:
						{
							fragment << line << '\n';
							break;
						}
					}

					continue;
				}
			}

			result[GL_VERTEX_SHADER] = vertex.str();
			result[GL_FRAGMENT_SHADER] = fragment.str();

			return result;
		}
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
	private:
		
		inline static std::string Trim(const std::string& str)
		{
			size_t start = str.find_first_not_of(" \t");
			if (start == std::string::npos) return "";
			size_t end = str.find_last_not_of(" \t");
			return str.substr(start, end - start + 1);
		}
		

	};

}