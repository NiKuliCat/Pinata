#pragma once
#include "RenderCommand.h"
#include "Shader.h"
#include "OrthographicCamera.h"
namespace Pinata {

	struct CameraData
	{
		glm::mat4 ViewProjectMatrix;
	};
	struct SceneData
	{
		CameraData mainCamera;
	};
	class Renderer
	{
	public:
		inline static RendererAPI::API GetAPI() { return  RendererAPI::GetAPI(); }

	public:

		static void BeginScene(OrthographicCamera* mainCamera);
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader);

	private:

		static  SceneData* m_SceneData;

	};
}