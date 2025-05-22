#pragma once
#include "Pinata/Scene/Scene.h"
#include "Pinata/Scene/Object.h"
#include "Pinata/Component/Tag.h"
namespace Pinata {


	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene);

		void SetContext(const Ref<Scene>& scene);
		
		void OnImGuiRender();

	private:
		void DrawObjectNode(Object obj);

	private:
		Ref<Scene> m_SceneContext;
		Object  m_SelectedObjectNode;
	};
}