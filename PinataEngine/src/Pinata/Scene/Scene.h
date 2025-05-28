#pragma once
#include "entt.hpp"
namespace Pinata {
	class Object;

	class Scene
	{

	public:
		Scene() = default;
		Scene(const std::string& name);
		~Scene();

		void OnUpdate(float deltaTime);

		entt::registry& GetRegistry() { return m_Registry; }
		Object CreateObject(const std::string& name);

		void DestroyObject(Object object);

	public:
		void RenderScene();

	private:
		std::string m_Name = "New Scene";
		entt::registry m_Registry;
		friend class SceneHierarchyPanel;
		friend class SceneSerialize;
	};
}