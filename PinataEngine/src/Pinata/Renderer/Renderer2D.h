#pragma once
#include "Texture.h"
#include "Material.h"
#include "Pinata/Component/Transform.h"
#include "Pinata/Renderer/Camera.h"
#include "Pinata/Editor/EditorCamera.h"
namespace Pinata {

	class Renderer2D
	{
	public:


		static void Init();
		static void Shutdown();
		static void BeginScene(Transform& transform,Camera& mainCamera);
		static void BeginScene(EditorCamera& editorCamera);
		static void EndScene();

		//with texture
		static void DrawQuad(glm::vec4& color, Ref<Texture2D>& texture);
		static void DrawQuad(Transform& transform, glm::vec4& color, Ref<Texture2D>& texture);
		static void DrawQuad(glm::vec3& position, glm::vec3& rotation, glm::vec3& scale, glm::vec4& color,Ref<Texture2D>& texture);

		//not with texture
		static void DrawQuad(glm::vec4& color);
		static void DrawQuad(Transform& transform, glm::vec4& color);
		static void DrawQuad(glm::vec3& position, glm::vec3& rotation, glm::vec3& scale, glm::vec4& color);


		// now use this api
		static void DrawQuad(Transform& transform, Ref<Material>& material);
		static void DrawQuadEditor(Transform& transform, Ref<Material>& material,int id);


	private:
		static void Flush();
	};
}