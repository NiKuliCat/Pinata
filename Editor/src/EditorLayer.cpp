#include "EditorLayer.h"

#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>
#include <glm/glm.hpp>
#include <chrono>
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

		m_Transform_A = Transform(glm::vec3(0.5f, 1.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.5f, 0.5f, 1.0f));
		m_Transform_B = Transform(glm::vec3(-3.0f, 0.0f, 0.1f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f));


		FrameBufferDescription disc;
		disc.Width = 1280;
		disc.Height = 720;
		m_FrameBuffer = FrameBuffer::Create(disc);
		m_ViewportSize = {(float) disc.Width,(float)disc.Height };


		m_Scene = CreateRef<Scene>("TestScene");
		auto obj = m_Scene->CreateObject("Test Square Object");
		obj.AddComponent<SpriteRenderer>(m_Material_A);

		auto obj2 = m_Scene->CreateObject("Test Square Object 2");
		auto& transform = obj2.GetComponent<Transform>(); //注意这里必须要引用，否则copy 下面修改无效
		transform.SetPosition(glm::vec3(-2.0f, 0.0f, 0.1f));
		obj2.AddComponent<SpriteRenderer>(m_Material_B);
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
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

//-----------------------------------My custom subWindow-----------------------------------
		ImVec2 ViewportSize;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding , ImVec2(0, 0));
		ImGui::Begin("Viewport");
		uint32_t ScreenRT_ID = m_FrameBuffer->GetColorRenderTexture();
		ViewportSize = ImGui::GetWindowSize();
		glm::vec2 CurrentSize = { ViewportSize.x,ViewportSize.y };
		if (m_ViewportSize != CurrentSize)
		{
			m_FrameBuffer->ReSize((uint32_t)CurrentSize.x, (uint32_t)CurrentSize.y);
			m_ViewportSize = CurrentSize;
			m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
		}
		ImGui::Image(ScreenRT_ID, ImVec2{ m_ViewportSize.x,m_ViewportSize.y },ImVec2(0,1),ImVec2(1,0));

		//PTA_INFO(ImGui::IsWindowFocused());
		//PTA_INFO(ImGui::IsWindowHovered());
		ImGui::End();
		ImGui::PopStyleVar();


		ImGui::Begin("Base Info");
		for (auto& profile : m_ProfileResults)
		{
			char label[50];
			strcpy(label, " %.3f ms  ");
			strcat(label, profile.name);

			ImGui::Text(label, profile.time);
		}
		ImGui::Text("FPS : %.3f per frame", 1.0f / m_TimeStep);
		ImGui::Text("Viewport Size : (%.0f,%.0f)", ViewportSize.x, ViewportSize.y);
		m_ProfileResults.clear();
		ImGui::End();

//-----------------------------------My custom subWindow-----------------------------------

		ImGui::End();
	}

	void EditorLayer::OnUpdate(float daltaTime)
	{


		m_TimeStep = daltaTime;
		PROFILE_SCOPE("TestLayer::OnUpdate");
		{
			PROFILE_SCOPE("CameraController::OnUpdate");
			m_CameraController.OnUpdate(daltaTime);
		}
		m_FrameBuffer->Bind();
		RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f,1.0f });
		RenderCommand::Clear();

		//2D render draw call
		{
			PROFILE_SCOPE("Renderer2D::BeginScene");
			Renderer2D::BeginScene(m_CameraController.GetCamera());
		}
		{

			m_Transform_A = Transform(glm::vec3(0.5f, 1.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(0.5f, 0.5f, 1.0f));
			m_Transform_B = Transform(glm::vec3(-1.0f, 0.0f, 0.1f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f));


			PROFILE_SCOPE("Renderer2D::DrawQuad");
			/*for (float i = 0.0f; i < 5.0f; i+= 1.0f)
			{
				for (float j = 0.0f; j < 5.0f; j += 1.0f)
				{
					m_Transform_A = Transform(glm::vec3(0.5f, 1.0f, 0.0f),
						glm::vec3(0.0f, 0.0f, 0.0f),
						glm::vec3(0.5f, 0.5f, 1.0f));

					m_Transform_B = Transform(glm::vec3(-0.5f, 0.0f, 0.1f),
						glm::vec3(0.0f, 0.0f, 0.0f),
						glm::vec3(1.0f, 1.0f, 1.0f));

					m_Transform_A.SetPosition(m_Transform_A.GetPosition() - glm::vec3(i * 0.6f, j * 0.6f, 0.0f));
					m_Transform_B.SetPosition(m_Transform_B.GetPosition() + glm::vec3(i * 1.2f, j * 1.2f, 0.0f));

					Renderer2D::DrawQuad(m_Transform_A, m_Material_A);
					Renderer2D::DrawQuad(m_Transform_B, m_Material_B);
				}
			}*/
			m_Scene->RenderScene();
		}

		Renderer2D::EndScene();
		m_FrameBuffer->UnBind();

	}

	void EditorLayer::OnEvent(Event& event)
	{
		m_CameraController.OnEvent(event);
	}
}