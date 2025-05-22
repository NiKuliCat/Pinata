#include "ptapch.h"
#include "SpriteRenderer.h"
namespace Pinata {
	SpriteRenderer::SpriteRenderer(Ref<Material>& material)
		:m_VertexColor(glm::vec4(1.0f)),m_Material(material)
	{
	}

	void SpriteRenderer::SetColor(const glm::vec4& color)
	{
		m_VertexColor = color;
		m_Material->SetColor(color);
	}

}