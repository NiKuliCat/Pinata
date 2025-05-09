#include "ptapch.h"
#include "Renderer.h"
namespace Pinata {

	SceneData* Renderer::m_SceneData = new SceneData;

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		//»·¾³£ºlights,map,
		m_SceneData->mainCamera.ViewProjectMatrix = camera.GetViewProjectionMatrix();
	}
	void Renderer::EndScene()
	{
		//m_SceneData->Clear()
	}
	void Renderer::SetBlend(bool enable)
	{
		RenderCommand::SetBlend(enable);
	}
	void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader)
	{
		vertexArray->Bind();
		shader->Register();
		shader->SetMat4("_ViewProjectMatrix",m_SceneData->mainCamera.ViewProjectMatrix);
		RenderCommand::DrawIndexed(vertexArray);
	}
}