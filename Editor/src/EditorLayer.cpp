#include "EditorLayer.h"

#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>
#include <glm/glm.hpp>
#include <chrono>
#include "MainCameraController.h"
#include "Pinata/Scene/SceneSerialize.h"
#include "Pinata/Utils/PlatformUtils.h"
#include "ImGuizmo.h"
namespace Pinata {
	void EditorLayer::OnAttach()
	{

		TextureAttributes attri;
		m_Texture2D_A = Texture2D::Create(attri, "Assets/Textures/02.png");
		m_Texture2D_B = Texture2D::Create(attri, "Assets/Textures/03.png");
		defaultWhiteTex = Texture2D::DefaultTexture(DefaultTexColor::Magenta);

		m_Shader = ShaderLibrary::Load("Assets/Shader/DefaultShader.shader");

		m_Material_A = Material::Create(m_Shader->GetID(), m_Texture2D_A);
		m_Material_B = Material::Create(m_Shader->GetID(), m_Texture2D_B);

		m_Transform_A = Transform(glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f));
		m_Transform_B = Transform(glm::vec3(-3.0f, 0.0f, 0.1f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f));


		FrameBufferDescription disc;
		disc.Width = 1280;
		disc.Height = 720;
		m_FrameBuffer = FrameBuffer::Create(disc);
		m_ViewportSize = { (float)disc.Width,(float)disc.Height };
		m_HasActiveScene = false;


#if 1
		m_Scene = CreateRef<Scene>("TestScene");

		{
			m_ScneneCamera = m_Scene->CreateObject("Main Camera");
			m_ScneneCamera.AddComponent<RuntimeCamera>();
			m_ScneneCamera.AddComponent<NativeScript>().Bind<MainCameraController>();
			auto& transform = m_ScneneCamera.GetComponent<Transform>();
			transform.Position = glm::vec3(0.0f, 0.0f, 10.0f);
			transform.Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
			m_ScneneCamera.GetComponent<RuntimeCamera>().OnDataChange();
			m_ScneneCamera.GetComponent<Tag>().m_Tag = AllTags::camera;
		}

		m_QuadObject = m_Scene->CreateObject("Square Object 1");
		m_QuadObject.AddComponent<SpriteRenderer>(m_Material_A);


		{
			auto obj = m_Scene->CreateObject("Square Object 2");
			auto& objtrans = obj.GetComponent<Transform>();
			objtrans.Position = glm::vec3(2.0f, 0.0f, 0.1f);
			obj.AddComponent<SpriteRenderer>(m_Material_A);
		}

		auto obj2 = m_Scene->CreateObject("Square Object 3");
		auto& transform = obj2.GetComponent<Transform>(); //注意这里必须要引用，否则copy 下面修改无效
		transform.Position = glm::vec3(-2.0f, 0.0f, 0.1f);
		obj2.AddComponent<SpriteRenderer>(m_Material_B);

		m_HierarchyPanel = SceneHierarchyPanel(m_Scene);
#endif // 0


		//SceneSerialize serialize(m_Scene);
		//serialize.Serialize("Assets/Scenes/TestScene.pta");
		//serialize.Deserialize("Assets/Scenes/TestScene.pta");

	}

	void EditorLayer::OnImGuiRender()
	{
		static bool p_open = true;
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		ImGui::Begin("DockSpace Demo", &p_open, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		ImVec2 minWindowSize = style.WindowMinSize;
		style.WindowMinSize = ImVec2{ 120.0f,80.0f };
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}
		style.WindowMinSize = minWindowSize;

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New","Ctrl+N"))
				{
					m_HasActiveScene = false;
					m_HierarchyPanel.SetContext(nullptr);

					m_Scene = CreateRef<Scene>("New Scene 1");
					m_HierarchyPanel.SetContext(m_Scene);
					m_HasActiveScene = true;
				}
				if (ImGui::MenuItem("Open...","Ctrl+O"))
				{
					std::string filepath = FileDialogs::OpenFile("Pinata Scene (*.pta)\0*.pta\0");
					if (!filepath.empty())
					{
						m_Scene = CreateRef<Scene>();

						m_HierarchyPanel.SetContext(m_Scene);
						SceneSerialize serialize(m_Scene);
						serialize.Deserialize(filepath);
						m_HasActiveScene = true;
					}
				}
				if (ImGui::MenuItem("Save As...","Ctrl+Shift+S",false, m_HasActiveScene))
				{
					std::string filepath = FileDialogs::SaveFile("Pinata Scene (*.pta)\0*.pta\0");
					if (!filepath.empty())
					{
						m_HierarchyPanel.SetContext(m_Scene);
						SceneSerialize serialize(m_Scene);
						serialize.Serialize(filepath);
					}
				}
				if (ImGui::MenuItem("Exit")) { Application::Get().CloseWindow(); }
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
//-----------------------------------My custom subWindow-----------------------------------

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding , ImVec2(0, 0));
		ImGui::Begin("Viewport");
		uint32_t ScreenRT_ID = m_FrameBuffer->GetColorRenderTexture();

		{
			ImVec2 ViewportSize = ImGui::GetContentRegionAvail();
			m_ViewportSize = { ViewportSize.x,ViewportSize.y };
		}

		ImGui::Image(ScreenRT_ID, ImVec2{ m_ViewportSize.x,m_ViewportSize.y },ImVec2(0,1),ImVec2(1,0));

		Object selectedObj = m_HierarchyPanel.GetSelectedObject();
		if (selectedObj)
		{
			//ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();
			float windowWidth = (float)ImGui::GetWindowWidth();
			float windowHeight = (float)ImGui::GetWindowHeight();
			ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

			auto cameraObj = m_Scene->GetMainCamera();
			const auto& camera = cameraObj.GetComponent<RuntimeCamera>();
			const auto& cameraTransform = cameraObj.GetComponent<Transform>();
			glm::mat4 viewMatrix = Transform::GetViewMatrix(cameraTransform);
			glm::mat4 projectionMatrix = camera.m_Camera.GetProjectionMatrix();


			auto& selectedObjTransform = selectedObj.GetComponent<Transform>();
			glm::mat4 modelMatrix = Transform::GetModelMatrix(selectedObjTransform);

			bool enableSnapping = Input::IsKeyPressed(Key::LeftControl);
			float snappingValue = 0.1f;
			if(m_GizmoControlType == ImGuizmo::OPERATION::ROTATE)
				snappingValue = 10.0f;
			float snappingValues[3] = { snappingValue,snappingValue,snappingValue };

			ImGuizmo::Manipulate(glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix),
								ImGuizmo::OPERATION(m_GizmoControlType), ImGuizmo::LOCAL, glm::value_ptr(modelMatrix),nullptr,enableSnapping ? snappingValues : nullptr);

			if (ImGuizmo::IsUsing())
			{
				glm::vec3 translate, rotate, scale;
				Transform::DecomposeTransformMatrix(modelMatrix, translate, rotate, scale);
				//先统一转成弧度计算 
				glm::vec3 currentRotate = glm::radians( selectedObjTransform.Rotation);
				glm::vec3 deltaRotate = rotate - currentRotate;
				currentRotate += deltaRotate;

				PTA_INFO("rotate:({0},{1},{2})", rotate.x, rotate.y, rotate.z);
				selectedObjTransform.Position = translate;
				//最后转回角度
				selectedObjTransform.Rotation = glm::degrees(currentRotate);
				selectedObjTransform.Scale = scale;
			}
		}

		ImGui::End();

		m_HierarchyPanel.OnImGuiRender();

		ImGui::Begin("Render Status ");
		for (auto& profile : m_ProfileResults)
		{
			char label[50];
			strcpy(label, " %.3f ms  ");
			strcat(label, profile.name);

			ImGui::Text(label, profile.time);
		}
		ImGui::Text("FPS : %.3f per frame", 1.0f / m_TimeStep);
		ImGui::Text("Viewport Size : (%.0f,%.0f)", m_ViewportSize.x, m_ViewportSize.y);

		m_ProfileResults.clear();
		ImGui::End();
//-----------------------------------My custom subWindow-----------------------------------


		ImGui::PopStyleVar();
		ImGui::End();
	}

	void EditorLayer::OnUpdate(float daltaTime)
	{


		m_TimeStep = daltaTime;
		if (m_ViewportSize.x != m_FrameBuffer->GetBufferDescription().Width || m_ViewportSize.y != m_FrameBuffer->GetBufferDescription().Height)
		{
			m_FrameBuffer->ReSize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			if (m_ScneneCamera)
			{
				m_ScneneCamera.GetComponent<RuntimeCamera>().m_Aspect = m_ViewportSize.x / m_ViewportSize.y;
				m_ScneneCamera.GetComponent<RuntimeCamera>().OnDataChange();
			}
		}

		m_FrameBuffer->Bind();
		RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f,1.0f });
		RenderCommand::Clear();
		if (m_Scene)
		{
			m_Scene->OnUpdate(daltaTime);
		}
		m_FrameBuffer->UnBind();

	}

	void EditorLayer::OnEvent(Event& event)
	{
		EventDisPatcher dispatcher(event);
		dispatcher.Dispatcher<KeyPressedEvent>(BIND_EVENT_FUNC(EditorLayer::OnKeyPressed));



	}

	bool  EditorLayer::OnKeyPressed(KeyPressedEvent& event)
	{
		if (event.IsRepeat())
			return false;


		switch (event.GetKeyCode())
		{
		case Key::W:
			m_GizmoControlType = ImGuizmo::OPERATION::TRANSLATE;
			break;
		case Key::E:
			m_GizmoControlType = ImGuizmo::OPERATION::ROTATE;
			break;
		case Key::R:
			m_GizmoControlType = ImGuizmo::OPERATION::SCALE;
			break;
		}
	}

}