#pragma once
#include "ptapch.h"
#include "Core.h"
#include "Window.h"
#include <Pinata/Event/ApplicationEvent.h>
namespace Pinata {

	class PINATA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		bool OnWindowClosed(WindowCloseEvent& evnet);

	};


	//to be defined in CLENT
	Application* CreateApplication();
}

