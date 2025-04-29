#pragma once
#include "RendererAPI.h"

namespace Pinata {

	class RenderCommand
	{
	public:
		inline static void Init()
		{
			s_RendererAPI->Init();
		}
		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}
		inline static void SetClearColor(const glm::vec4 color)
		{
			s_RendererAPI->SetClearColor(color);
		}
		inline static void SetBlend(bool enable)
		{
			s_RendererAPI->SetBlend(enable);
		}
		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}

	private:
		static RendererAPI* s_RendererAPI;
	};
}