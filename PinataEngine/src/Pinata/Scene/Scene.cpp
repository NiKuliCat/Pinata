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

	void Scene::OnUpdateRuntime(float deltaTime)
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
		RenderSceneRunTime();
	}

	void Scene::OnUpdateEditor(float deltaTime,EditorCamera& editorCamera)
	{
		RenderSceneEditor(editorCamera);
	}

	Object Scene::CreateObject(const std::string& name)
	{
		
		Object obj = {m_Registry.create(), this };
		obj.AddComponent<Tag>(AllTags::default);
		obj.AddComponent<Name>(name);
		obj.AddComponent<Transform>();
		return obj;
	}

	void Scene::DestroyObject(Object object)
	{
		m_Registry.destroy(object);
	}


	void Scene::RenderSceneRunTime()
	{
		Camera* MainCamera = nullptr;
		Transform MainCameraTransform;
		auto group = m_Registry.group<Transform, RuntimeCamera>();
		int sort = -1;
		for (auto obj : group)
		{
			auto [transform, camera] = group.get<Transform, RuntimeCamera>(obj);
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
			auto group = m_Registry.group<Transform,SpriteRenderer>();
			for (auto obj : group)
			{
				auto [transform, spriteRenderer] = group.get<Transform, SpriteRenderer>(obj);
				Renderer2D::DrawQuad(transform, spriteRenderer.GetMaterial());
			}

			Renderer2D::EndScene();
		}
	}

	void Scene::RenderSceneEditor(EditorCamera& editorCamera)
	{
		Renderer2D::BeginScene(editorCamera);

		auto group = m_Registry.group<Transform, SpriteRenderer>();
		for (auto obj : group)
		{
			auto [transform, spriteRenderer] = group.get<Transform, SpriteRenderer>(obj);
			Renderer2D::DrawQuadEditor(transform, spriteRenderer.GetMaterial(), (int)obj);
		}

		Renderer2D::EndScene();
	}

	Object Scene::GetMainCamera()
	{
		entt::entity cameraEntity;
		auto view = m_Registry.view<RuntimeCamera>();
		int sort = -1;
		for (auto camera : view)
		{
			auto cameraComponent  = view.get< RuntimeCamera>(camera);
			if (cameraComponent.m_Sort > sort)
			{
				cameraEntity = camera;
				sort = cameraComponent.m_Sort;
			}
		}
		if (sort != -1)
		{
			return Object{ cameraEntity,this };
		}
		return {};
	}

}