#include "ptapch.h"
#include "Renderer.h"
namespace Pinata {

	SceneData* Renderer::m_SceneData = new SceneData;

	void Renderer::BeginScene(OrthographicCamera* camera)
	{
		//»·¾³£ºlights,map,
		m_SceneData->mainCamera.ViewProjectMatrix = camera->GetViewProjectionMatrix();
	}
	void Renderer::EndScene()
	{
		//m_SceneData->Clear()
	}
	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader)
	{
		vertexArray->Bind();
		shader->Register();
		shader->SetMat4("_ViewProjectMatrix",m_SceneData->mainCamera.ViewProjectMatrix);
		RenderCommand::DrawIndexed(vertexArray);
	}
}