#include "ptapch.h"
#include "Renderer.h"
#include "RenderCommand.h"
namespace Pinata {

	void Renderer::BeginScene()
	{
		//»·¾³£ºlights,map,
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}