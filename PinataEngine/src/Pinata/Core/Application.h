#pragma once
#include "ptapch.h"
#include "Core.h"
#include "Window.h"
#include "Pinata/Core/LayerStack.h"
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

	private:
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
		bool m_Running = true;

		bool OnWindowClosed(WindowCloseEvent& evnet);

	};


	//to be defined in CLENT
	Application* CreateApplication();
}

