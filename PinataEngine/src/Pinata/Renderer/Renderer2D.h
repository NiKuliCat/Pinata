#pragma once
#include "OrthographicCamera.h"
#include "Texture.h"
#include "Pinata/Object/Transform.h"
namespace Pinata {

	class Renderer2D
	{
	public:


		static void Init();
		static void Shutdown();
		static void BeginScene(OrthographicCamera& mainCamera);
		static void EndScene();

		static void DrawQuad(glm::vec4& color, Ref<Texture2D>& texture);
		static void DrawQuad(Transform& transform, glm::vec4& color, Ref<Texture2D>& texture);
		static void DrawQuad(glm::vec3& position, glm::vec3& rotation, glm::vec3& scale, glm::vec4& color,Ref<Texture2D>& texture);


		//TODO   add material system 
		//static void DrawQuad(Transform& transform,Material& mat);
	};
}