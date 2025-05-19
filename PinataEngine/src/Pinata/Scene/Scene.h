#pragma once
#include "entt.hpp"
namespace Pinata {
	class Object;
	class Scene
	{

	public:

		Scene(const std::string& name);
		~Scene();

		void OnUpdata(float deltaTime);

		entt::registry& GetRegistry() { return m_Registry; }
		Object CreateObject(const std::string& name);

	public:
		void RenderScene();

	private:
		std::string m_Name;
		entt::registry m_Registry;
	};
}