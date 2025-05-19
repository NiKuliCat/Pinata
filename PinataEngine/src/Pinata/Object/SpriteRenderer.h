#pragma once
#include "Pinata/Renderer/Material.h"
#include <glm/glm.hpp>
namespace Pinata {


	class SpriteRenderer
	{
	public:
		SpriteRenderer() = default;
		SpriteRenderer(Ref<Material>& material);
		~SpriteRenderer() = default;

	public:
		void SetColor(const glm::vec4& color) { m_VertexColor = color; }
		glm::vec4& GetColor() { return m_VertexColor; }
		const glm::vec3&  GetColor() const { return m_VertexColor; }

		Ref<Material>& GetMaterial() { return m_Material; }
		const Ref<Material>& GetMaterial() const  { return m_Material; }

	private:
		glm::vec4 m_VertexColor = { 1.0f,1.0f,1.0f,1.0f };
		Ref<Material> m_Material;
	};
}