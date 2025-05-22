#pragma once
#include "RenderCommand.h"
#include "Shader.h"
#include "OrthographicCamera.h"
namespace Pinata {

	struct CameraData
	{
		glm::mat4 ViewProjectMatrix;
	};

	struct LightsData
	{

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
		static void Init();
		static void BeginScene(OrthographicCamera& mainCamera);
		static void EndScene();
		static void SetWindowSize(const uint32_t width, const uint32_t height);
		static void SetBlend(bool enable);
		static void SetDepthTest(bool enable);
		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader);
		static void Submit(const Ref<VertexArray>& vertexArray,glm::mat4& model,const Ref<Shader>& shader);
		static void Submit(const Ref<VertexArray>& vertexArray,uint32_t count, glm::mat4& model, const Ref<Shader>& shader);
	private:

		static  SceneData* m_SceneData;

	};
}