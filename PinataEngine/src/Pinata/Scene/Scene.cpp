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
		RenderScene();
	}

	Object Scene::CreateObject(const std::string& name)
	{
		
		Object obj = {m_Registry.create(), this };
		obj.AddComponent<Tag>(AllTags::default);
		obj.AddComponent<Name>(name);
		obj.AddComponent<Transform>();
		return obj;
	}


	void Scene::RenderScene()
	{
		Camera* MainCamera = nullptr;
		Transform MainCameraTransform;
		auto view = m_Registry.view<Transform, RuntimeCamera>();
		int sort = -1;
		for (auto camera : view)
		{
			auto [transform, camera] = view.get<Transform, RuntimeCamera>(camera);
			if (camera.m_Sort > sort)
			{
				MainCameraTransform = transform;
				MainCamera = &camera.m_Camera;
				sort = camera.m_Sort;
			}
		}

		if (MainCamera)
		{
			Renderer2D::BeginScene(MainCameraTransform, *MainCamera);
			auto group = m_Registry.group<Transform>(entt::get<SpriteRenderer>);
			int i = 0;
			for (auto obj : group)
			{
				i++;
				auto [transform, spriteRenderer] = group.get<Transform, SpriteRenderer>(obj);
				Renderer2D::DrawQuad(transform, spriteRenderer.GetMaterial());
			}

			Renderer2D::EndScene();
		}
	}

}