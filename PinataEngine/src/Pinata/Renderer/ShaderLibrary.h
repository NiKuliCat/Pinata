#pragma once

#include <unordered_map>
#include "Shader.h"
namespace Pinata {



	class ShaderLibrary
	{
	public:
		static void Add(Ref<Shader>& shader);
		static void Remove(uint32_t id);
		static Ref<Shader> Load(const std::string& filepath);

		static Ref<Shader> Get(const uint32_t id);


	private:
		static bool Exists(const uint32_t id);
	private:
		static std::unordered_map<uint32_t, Ref<Shader>> m_Shaders;
	};
}