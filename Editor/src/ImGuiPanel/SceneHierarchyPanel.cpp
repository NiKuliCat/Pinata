#include "ptapch.h"
#include "SceneHierarchyPanel.h"
#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>
#include "Pinata/Component/Component.h"
#include <glm/gtc/type_ptr.hpp>
namespace Pinata{
	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& scene)
	{
		SetContext(scene);
	}
	void SceneHierarchyPanel::SetContext(const Ref<Scene>& scene)
	{
		m_SceneContext = scene;
		m_SelectedObjectNode = {};
	}
	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Hierarchy");

		if (m_SceneContext)
		{
			ImGuiIO& io = ImGui::GetIO();
			auto boldfont = io.Fonts->Fonts[1];
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_DefaultOpen;

			ImGui::PushFont(boldfont);
			bool open = ImGui::TreeNodeEx(m_SceneContext->m_Name.c_str(), flags);
			ImGui::PopFont();
			if (ImGui::IsItemClicked())
			{
				m_SelectedObjectNode = {};
			}
			if (open)
			{
				m_SceneContext->GetRegistry().view<entt::entity>().each([&](auto entityID)
					{

						Object obj{ entityID, m_SceneContext.get() };
						DrawObjectNode(obj);
					});

				ImGui::TreePop();
			}


			if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			{
				m_SelectedObjectNode = {};
			}

			if (!ImGui::IsAnyItemHovered() && ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
			{

				ImGui::OpenPopup("hierarchy_context_menu");
			}

			if (ImGui::BeginPopup("hierarchy_context_menu")) {
				if (ImGui::MenuItem("Create Empty Object")) { m_SceneContext->CreateObject("Empty Object"); }
				if (ImGui::MenuItem("Create Quad ")) { m_SceneContext->CreateObject("Quad Object"); }
				ImGui::EndPopup();
			}
		}

		ImGui::End();
		DrawInspectorPanel();

	}

	void SceneHierarchyPanel::DrawObjectNode(Object obj)
	{
		auto& name = obj.GetName();
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ((m_SelectedObjectNode == obj) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_SpanAvailWidth;

		bool open = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)obj, flags, name.c_str());

		if (ImGui::IsItemClicked())
		{
			m_SelectedObjectNode = obj;
		}

		bool deleted = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete"))
			{
				deleted = true;
			}
			ImGui::EndPopup();
		}

		if (open)
		{

			ImGui::TreePop();
		}
		if (deleted)
		{
			m_SceneContext->DestroyObject(obj);
			if (m_SelectedObjectNode == obj)
			{
				m_SelectedObjectNode = {};
			}
		}
	}
	template<typename T, typename Func>
	static void DrawComponent(const std::string& label, Object object, Func func,bool enableRemove = true)
	{
		const ImGuiTreeNodeFlags componentNodeFlags = ImGuiTreeNodeFlags_DefaultOpen  | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_AllowOverlap
														| ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding;
		const std::string moreOperation_Str = "Component More Operation";
		if (object.HasComponent<T>())
		{
			auto& component = object.GetComponent<T>();
			ImVec2 contentAvailabel = ImGui::GetContentRegionAvail();

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImGui::Separator();
			bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), componentNodeFlags, label.c_str());
			ImGui::PopStyleVar();

			ImGui::SameLine(contentAvailabel.x - lineHeight * 0.5f);
			if (ImGui::Button("+", ImVec2{ lineHeight,lineHeight }))
			{
				ImGui::OpenPopup(moreOperation_Str.c_str());
			}

			bool remove = false;

			if (ImGui::BeginPopup(moreOperation_Str.c_str()))
			{
				if (ImGui::MenuItem("Remove Component",0,false, enableRemove))
				{
					remove = true;
				}
				ImGui::EndPopup();
			}

			if (open)
			{
				func(component);
				ImGui::TreePop();
			}

			if (remove)
			{
				object.RemoveComponent<T>();
			}
		}
	}

	static void DrawVec3Control(const std::string& label, glm::vec3& value, glm::vec3& defaulValue = glm::vec3( 0.0f,0.0f,0.0f ), float columnWidth = 90.0f)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto boldfont = io.Fonts->Fonts[1];
		ImGui::PushID(label.c_str());
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();
		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 1,1 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 10.0f,lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.7f,0.1f,0.15f,1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f,0.2f,0.25f,1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.7f,0.1f,0.15f,1.0f });
		ImGui::PushFont(boldfont);
		if (ImGui::Button("X", buttonSize))
		{
			value.x = defaulValue.x;
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragFloat("##X", &value.x, 0.04f,0.0f,0.0f,"%.2f"); // float input
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f,0.7f,0.1f,1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f,0.9f,0.3f,1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f,0.9f,0.15f,1.0f });
		ImGui::PushFont(boldfont);
		if (ImGui::Button("Y", buttonSize))
		{
			value.y = defaulValue.y;
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragFloat("##Y", &value.y, 0.1f, 0.0f, 0.0f, "%.2f"); // float input
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f,0.1f,0.7f,1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f,0.2f,0.9f,1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f,0.2f,0.9f,1.0f });
		ImGui::PushFont(boldfont);
		if (ImGui::Button("Z", buttonSize))
		{
			value.z = defaulValue.z;
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragFloat("##Z", &value.z, 0.03f, 0.0f, 0.0f, "%.2f"); // float input
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();
		ImGui::Columns(1);

		ImGui::PopID();
	}



	void SceneHierarchyPanel::DrawInspectorPanel()
	{
		ImGui::Begin("Inspector");
		if (m_SelectedObjectNode)
		{

#pragma region  ------------------------------------------------- Draw Name Component ---------------------------------------------------------

			if (m_SelectedObjectNode.HasComponent<Name>())
			{
				ImGui::Columns(2);
				ImGui::SetColumnWidth(0, 120.0f);
				ImGui::Text("Name : ");
				ImGui::NextColumn();
				auto& name = m_SelectedObjectNode.GetComponent<Name>().m_Name;
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

#pragma region  ------------------------------------------------- Draw Transform Component ---------------------------------------------------------
			DrawComponent<Transform>("Transform", m_SelectedObjectNode, [this](auto& transformComponent) {
				DrawVec3Control("Position", transformComponent.Position);
				DrawVec3Control("Rotation", transformComponent.Rotation);
				DrawVec3Control("Scale", transformComponent.Scale, glm::vec3(1.0f, 1.0f, 1.0f));
				},false);
#pragma endregion

#pragma region  ------------------------------------------------- Draw Camera Component ---------------------------------------------------------
			DrawComponent<RuntimeCamera>("Camera", m_SelectedObjectNode, [this](auto& cameraComponent) {

				const char* projectionMode_str[] = { "Orthographic","Perspective" };
				const char* currentMode_str = projectionMode_str[(int)cameraComponent.m_ProjectionMode];
				if (ImGui::BeginCombo("Projection Mode", currentMode_str))
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
					if (ImGui::DragFloat("fov", &cameraComponent.m_FOV, 1.0f, 0.05f, 160.0f))
					{
						cameraComponent.OnDataChange();
					}
					if (ImGui::DragFloat("near", &cameraComponent.m_Near, 1.0f, 0.01f, 100.0f))
					{
						cameraComponent.OnDataChange();
					}
					if (ImGui::DragFloat("far", &cameraComponent.m_Far, 1.0f, 1.0f, 200.0f))
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

				});
#pragma endregion

			
		}
		ImGui::End();

	}

	void SceneHierarchyPanel::OnSlectedObjectChange(Object obj)
	{
		m_SelectedObjectNode = obj;
		auto storage = m_SceneContext->GetRegistry().storage();

	}
}