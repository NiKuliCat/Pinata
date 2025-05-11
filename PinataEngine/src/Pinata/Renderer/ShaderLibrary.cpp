#include "ptapch.h"
#include "ShaderLibrary.h"

namespace Pinata {

	std::unordered_map<uint32_t, Ref<Shader>> ShaderLibrary::m_Shaders = std::unordered_map<uint32_t, Ref<Shader>>();
	void ShaderLibrary::Add(Ref<Shader>& shader)
	{
		uint32_t id = shader->GetID();
		if (Exists(id))
		{
			PTA_CORE_WARN("the shader {0} is exist ", shader->GetName());
			return;
		}

		m_Shaders[id] = shader;

	}
	void ShaderLibrary::Remove(uint32_t id)
	{
		if (!Exists(id))
		{
			PTA_CORE_WARN("shader not find");
			return;
		}
		m_Shaders.erase(id);
	}
	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Creat(filepath);
		Add(shader);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Get(const uint32_t id)
	{
		if (!Exists(id))
		{
			PTA_CORE_WARN("shader not find");
			return nullptr;
		}
		return m_Shaders[id];

	}
	bool ShaderLibrary::Exists(const uint32_t id)
	{
		return m_Shaders.find(id) != m_Shaders.end();
	}
}