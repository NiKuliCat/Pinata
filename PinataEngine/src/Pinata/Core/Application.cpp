#include "ptapch.h"
#include "Application.h"
#include "Log.h"
#include "Pinata/Event/ApplicationEvent.h"
namespace Pinata {

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdata();
		}
	}
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}
	Application::~Application()
	{
	}
}
