#include "ptapch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include "Pinata/Core/Application.h"
#include "ImGuizmo.h"
namespace Pinata {
	ImGuiLayer::ImGuiLayer()
		:Layer("ImGuiLayer")
	{
	}
	ImGuiLayer::~ImGuiLayer()
	{

	}
	void ImGuiLayer::OnAttach()
	{

//-----------------------------Init ImGui--look at url:https://github.com/ocornut/imgui/wiki/Getting-Started
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

        ImGui::StyleColorsDark();
        SetDarkThemeColor();
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        auto window = (GLFWwindow*) Application::Get().GetWindow().GetNativeWindow();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");

        //font
        ImFontConfig fontcfg;
        fontcfg.GlyphOffset.x = -1.0f;
        ImFont* font = io.Fonts->AddFontFromFileTTF("Assets/Fonts/Rubik/Rubik-VariableFont_wght.ttf", 20.0f, &fontcfg, io.Fonts->GetGlyphRangesChineseFull());
        io.Fonts->AddFontFromFileTTF("Assets/Fonts/Rubik/Rubik-SemiBold.ttf", 20.0f);
        ImGui::GetIO().FontDefault = font;

        ImGui_ImplOpenGL3_DestroyFontsTexture();
        ImGui_ImplOpenGL3_CreateFontsTexture();
	}
	void ImGuiLayer::OnDetach()
	{
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
	}
	


    void ImGuiLayer::SetDarkThemeColor()
    {
        auto& colors = ImGui::GetStyle().Colors;

        colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f,0.105f,0.11f,1.0f };

        //header
        colors[ImGuiCol_Header] = ImVec4{ 0.25f,0.255f,0.26f,1.0f };
        colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.35f,0.355f,0.36f,1.0f };
        colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f,0.155f,0.16f,1.0f };

        //button
        colors[ImGuiCol_Button] = ImVec4{ 0.25f,0.255f,0.26f,1.0f };
        colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.35f,0.355f,0.36f,1.0f };
        colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f,0.155f,0.16f,1.0f };

        //frame background
        colors[ImGuiCol_FrameBg] = ImVec4{ 0.25f,0.255f,0.26f,1.0f };
        colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.35f,0.355f,0.36f,1.0f };
        colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f,0.155f,0.16f,1.0f };

        //tab
        colors[ImGuiCol_Tab] = ImVec4{ 0.25f,0.255f,0.26f,1.0f };
        colors[ImGuiCol_TabHovered] = ImVec4{ 0.35f,0.355f,0.36f,1.0f };
        colors[ImGuiCol_TabActive] = ImVec4{ 0.25f,0.255f,0.26f,1.0f };
        colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f,0.155f,0.16f,1.0f };
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.25f,0.255f,0.26f,1.0f };

        //title
        colors[ImGuiCol_TitleBg] = ImVec4{ 0.18f,0.185f,0.19f,1.0f };
        colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.35f,0.355f,0.36f,1.0f };
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.25f,0.255f,0.26f,1.0f };
       
    }

    void ImGuiLayer::Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGuizmo::BeginFrame();
    }
    void ImGuiLayer::End()
    {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }
    void ImGuiLayer::OnImGuiRender()
    {
        //static bool show = true;
        //ImGui::ShowDemoWindow(&show);
    }

}