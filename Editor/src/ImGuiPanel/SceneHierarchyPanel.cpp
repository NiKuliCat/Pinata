#include "ptapch.h"
#include "SceneHierarchyPanel.h"
#include <ImGui/imgui.h>

namespace Pinata{
	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& scene)
	{
		SetContext(scene);
	}
	void SceneHierarchyPanel::SetContext(const Ref<Scene>& scene)
	{
		m_SceneContext = scene;
	}
	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Hierarchy");
		m_SceneContext->GetRegistry().view<entt::entity>().each([&](auto entityID)
			{
				Object obj{ entityID, m_SceneContext.get() };
				DrawObjectNode(obj);
			});
		ImGui::End();

	}
	void SceneHierarchyPanel::DrawObjectNode(Object obj)
	{
		auto& name = obj.GetName();
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ((m_SelectedObjectNode == obj) ? ImGuiTreeNodeFlags_Selected : 0);

		bool open = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)obj, flags, name.c_str());

		if (ImGui::IsItemClicked())
			m_SelectedObjectNode = obj;

		if (open)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
			bool open = ImGui::TreeNodeEx((void*)12223, flags, "My Chlid");
			if (open)
				ImGui::TreePop();

			ImGui::TreePop();
		}
	}
}