#pragma once
#include "Pinata/Scene/Scene.h"
#include "Pinata/Scene/Object.h"
namespace Pinata {


	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene);

		void SetContext(const Ref<Scene>& scene);
		Object GetSelectedObject() { return m_SelectedObjectNode; }
		void OnImGuiRender();
		operator bool() const { return !(m_SceneContext == nullptr); }
	private:
		void DrawObjectNode(Object obj);
		void DrawInspectorPanel();
		void OnSlectedObjectChange(Object obj);
	private:
		Ref<Scene> m_SceneContext;
		Object  m_SelectedObjectNode;
	};
}