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

#pragma region  ------------------------------------------------- Name Component ---------------------------------------------------------

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
#pragma endregion

			if (m_SelectedObjectNode.HasComponent<Transform>())
			{

			}

			if (m_SelectedObjectNode.HasComponent<RuntimeCamera>())
			{
				if (ImGui::TreeNodeEx((void*)typeid(RuntimeCamera).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Camera"))
				{
					auto& cameraComponent = m_SelectedObjectNode.GetComponent<RuntimeCamera>();

					const char* projectionMode_str[] = { "Orthographic","Perspective" };
					const char* currentMode_str = projectionMode_str[(int)cameraComponent.m_ProjectionMode];
					if(ImGui::BeginCombo("Projection Mode", currentMode_str))
					{
						for (int i = 0; i < 2; i++)
						{
							bool isSelected = currentMode_str == projectionMode_str[i];
							if (ImGui::Selectable(projectionMode_str[i], isSelected))
							{
								currentMode_str = projectionMode_str[i];
								cameraComponent.m_ProjectionMode = (ProjectionMode)i;
								PTA_INFO("main camera info :fov:{1},aspect{2},near{3},far{4}",
									cameraComponent.m_FOV, cameraComponent.m_Aspect,
									cameraComponent.m_Near, cameraComponent.m_Far);

								cameraComponent.OnDataChange();
							}

							if (isSelected)
							{
								ImGui::SetItemDefaultFocus();
							}
						}

						ImGui::EndCombo();
					}

					if (cameraComponent.m_ProjectionMode == ProjectionMode::Perspective)
					{
						if (ImGui::DragFloat("fov", &cameraComponent.m_FOV,1.0f,0.05f,160.0f))
						{
							cameraComponent.OnDataChange();
						}
						if (ImGui::DragFloat("near", &cameraComponent.m_Near, 1.0f, 0.01f,100.0f))
						{
							cameraComponent.OnDataChange();
						}
						if (ImGui::DragFloat("far", &cameraComponent.m_Far,1.0f, 1.0f,200.0f))
						{
							cameraComponent.OnDataChange();
						}
					}
					if (cameraComponent.m_ProjectionMode == ProjectionMode::Orthographic)
					{

						if (ImGui::DragFloat("orth size", &cameraComponent.m_OrthSize, 0.1f, 0.05f, 10.0f))
						{
							cameraComponent.OnDataChange();
						}
						if (ImGui::DragFloat("orth near", &cameraComponent.m_Near, 0.2f, 0.01f, 100.0f))
						{
							cameraComponent.OnDataChange();
						}
						if (ImGui::DragFloat("orth far", &cameraComponent.m_Far, 0.2f, 1.0f, 200.0f))
						{
							cameraComponent.OnDataChange();
						}
					}



					ImGui::TreePop();
				}
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