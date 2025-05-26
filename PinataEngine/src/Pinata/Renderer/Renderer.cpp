#include "ptapch.h"
#include "Renderer.h"
#include "Renderer2D.h"
namespace Pinata {

	SceneData* Renderer::m_SceneData = new SceneData;

	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		//»·¾³£ºlights,map,
		m_SceneData->mainCamera.ViewProjectMatrix = camera.GetViewProjectionMatrix();
	}
	void Renderer::BeginScene(Transform& transform,Camera& mainCamera)
	{
		m_SceneData->mainCamera.ViewProjectMatrix = mainCamera.GetProjectionMatrix() * Transform::GetViewMatrix(transform);
	}
	void Renderer::EndScene()
	{
		//m_SceneData->Clear()
	}
	void Renderer::SetWindowSize(const uint32_t width, const uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}
	void Renderer::SetBlend(bool enable)
	{
		RenderCommand::SetBlend(enable);
	}
	void Renderer::SetDepthTest(bool enable)
	{
		RenderCommand::SetDepthTest(enable);
	}
	void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader)
	{
		vertexArray->Bind();
		shader->Bind();
		shader->SetMat4("_MVP",m_SceneData->mainCamera.ViewProjectMatrix);
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::Submit(const Ref<VertexArray>& vertexArray, glm::mat4& model, const Ref<Shader>& shader )
	{
		vertexArray->Bind();
		shader->Bind();
		glm::mat4 mvp = m_SceneData->mainCamera.ViewProjectMatrix * model ;
		shader->SetMat4("_MVP", mvp);
		RenderCommand::DrawIndexed(vertexArray);
	}
	void Renderer::Submit(const Ref<VertexArray>& vertexArray, uint32_t count, glm::mat4& model, const Ref<Shader>& shader)
	{
		vertexArray->Bind();
		shader->Bind();
		glm::mat4 mvp = m_SceneData->mainCamera.ViewProjectMatrix * model;
		shader->SetMat4("_MVP", mvp);
		RenderCommand::DrawIndexed(vertexArray,count);
	}
}