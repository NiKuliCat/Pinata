#pragma once
#include "entt.hpp"
#include "Pinata/Editor/EditorCamera.h"
namespace Pinata {
	class Object;

	class Scene
	{

	public:
		Scene() = default;
		Scene(const std::string& name);
		~Scene();

		void OnUpdateRuntime(float deltaTime);
		void OnUpdateEditor(float deltaTime,EditorCamera& editorCamera);

		entt::registry& GetRegistry() { return m_Registry; }
		Object CreateObject(const std::string& name);

		void DestroyObject(Object object);

	public:
		void RenderSceneRunTime();
		void RenderSceneEditor(EditorCamera& editorCamera);

		Object GetMainCamera();

	private:

		std::string m_Name = "New Scene";
		entt::registry m_Registry;
		friend class SceneHierarchyPanel;
		friend class SceneSerialize;
	};
}