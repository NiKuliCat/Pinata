#pragma once
#include "ptapch.h"
#include "Core.h"
#include "Window.h"
namespace Pinata {

	class PINATA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

	};


	//to be defined in CLENT
	Application* CreateApplication();
}

