#pragma once
#include "ptapch.h"
#include "Core.h"
#include "Window.h"
#include "Pinata/Core/LayerStack.h"
#include "Pinata/ImGui/ImGuiLayer.h"
#include <Pinata/Event/ApplicationEvent.h>
namespace Pinata {

	class PINATA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
		bool m_Running = true;
		static Application* s_Instance;

		bool OnWindowClosed(WindowCloseEvent& evnet);

		unsigned int m_VertexArray, m_IndexBuffer, m_VertexBuffer;

	};


	//to be defined in CLENT
	Application* CreateApplication();
}

