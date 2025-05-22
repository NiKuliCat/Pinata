#include "ptapch.h""
#include "Scene.h"
#include "Object.h"
#include "Pinata/Component/Component.h"
#include "Pinata/Renderer/Renderer2D.h"
namespace Pinata {

	Scene::Scene(const std::string& name)
		:m_Name(name)
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::OnUpdate(float deltaTime)
	{
		{
			m_Registry.view<NativeScript>().each([=](auto entity, auto& nsc)
			{
				if (!nsc.Instance)
				{
					nsc.Instance = nsc.InstantiateScript();
					nsc.Instance->m_Object = Object(entity, this);
					nsc.Instance->OnCreate();
				}
				nsc.Instance->OnUpdate(deltaTime);

			});
		}
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