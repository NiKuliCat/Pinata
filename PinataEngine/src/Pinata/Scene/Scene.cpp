#include "ptapch.h""
#include "Scene.h"
#include "Object.h"
#include "Pinata/Object/Component.h"
#include "Pinata/Renderer/Renderer2D.h"
namespace Pinata {

	Scene::Scene(const std::string& name)
		:m_Name(name)
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::OnUpdata(float deltaTime)
	{

	}

	Object Scene::CreateObject(const std::string& name)
	{
		Object obj = { name,m_Registry.create(),this };
		obj.AddComponent<Transform>();
		return obj;
	}

	void Scene::RenderScene()
	{
		auto group = m_Registry.group<Transform>(entt::get<SpriteRenderer>);
		for (auto obj : group)
		{
			auto [transform, spriteRenderer] = group.get<Transform, SpriteRenderer>(obj);
			Renderer2D::DrawQuad(transform, spriteRenderer.GetMaterial());
		}
	}

}