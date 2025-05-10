#pragma once
#include "Pinata/Renderer/RendererAPI.h"

namespace Pinata {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void Clear() override;
		virtual void SetClearColor(const glm::vec4 color) override;
		virtual void SetBlend(bool value) override;
		virtual void SetDepthTest(bool value) override;
		virtual void SetViewport(const uint32_t x, const uint32_t y, const  uint32_t width, const uint32_t height) override;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};
}