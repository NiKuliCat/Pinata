#pragma once
#include "ptapch.h"
#include "Core.h"
#include "Window.h"
#include "Pinata/Core/LayerStack.h"
#include "Pinata/ImGui/ImGuiLayer.h"
#include "Pinata/Renderer/Shader.h"
#include "Pinata/Renderer/Buffer.h"
#include "Pinata/Renderer/VertexArray.h"
#include "Pinata/Event/ApplicationEvent.h"

namespace Pinata {

	class PINATA_API Application
	{
	public:
		Application(const std::string& name);
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
		inline void CloseWindow() { m_Running = false; }
	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
		bool m_Running = true;
		bool m_Minimized = false;
		static Application* s_Instance;

		bool OnWindowClosed(WindowCloseEvent& event);
		bool OnWindowResize(WindowResizeEvent& event);

	};


	//to be defined in CLENT
	Application* CreateApplication();
}

