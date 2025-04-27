#pragma once
#include "RendererAPI.h"
namespace Pinata {

	class Renderer
	{
	public:
		inline static RendererAPI::API GetAPI() { return  RendererAPI::GetAPI(); }

	public:

		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
	};
}