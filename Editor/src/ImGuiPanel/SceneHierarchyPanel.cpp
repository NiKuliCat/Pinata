#include "ptapch.h"
#include "SceneHierarchyPanel.h"
#include <ImGui/imgui.h>
#include "Pinata/Component/Component.h"
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


		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
		{
			m_SelectedObjectNode = {};
		}
		ImGui::End();



		DrawInspectorPanel();

	}
	void SceneHierarchyPanel::DrawObjectNode(Object obj)
	{
		auto& name = obj.GetName();
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ((m_SelectedObjectNode == obj) ? ImGuiTreeNodeFlags_Selected : 0);

		bool open = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)obj, flags, name.c_str());

		if (ImGui::IsItemClicked())
		{
			m_SelectedObjectNode = obj;
		}

		if (open)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
			bool open = ImGui::TreeNodeEx((void*)12223, flags, "My Chlid");
			if (open)
				ImGui::TreePop();

			ImGui::TreePop();
		}
	}

	void SceneHierarchyPanel::DrawInspectorPanel()
	{
		ImGui::Begin("Inspector");
		if (m_SelectedObjectNode)
		{
			if (m_SelectedObjectNode.HasComponent<Name>())
			{
				ImGui::Columns(2, "##Columns", false);
				ImGui::SetColumnWidth(0, 120.0f);
				ImGui::Text("Name : ");
				ImGui::NextColumn();
				auto& name = m_SelectedObjectNode.GetComponent<Name>().GetName();
				char buffer[256];
				memset(buffer, 0, sizeof(buffer));
				strcpy_s(buffer, sizeof(buffer), name.c_str());
				if (ImGui::InputText("##Name", buffer, sizeof(buffer)))
				{
					name = std::string(buffer);
				}
				ImGui::Columns(1);
			}

			if (m_SelectedObjectNode.HasComponent<Transform>())
			{

			}

			if (m_SelectedObjectNode.HasComponent<RuntimeCamera>())
			{

			}
		}
		ImGui::End();

	}

	void SceneHierarchyPanel::OnSlectedObjectChange(Object obj)
	{
		m_SelectedObjectNode = obj;
		auto storage = m_SceneContext->GetRegistry().storage();

	}
}