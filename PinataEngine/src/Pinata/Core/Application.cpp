#include "ptapch.h"
#include "Application.h"
#include "Pinata/Event/ApplicationEvent.h"
#include <GLFW/glfw3.h>
namespace Pinata {

#define BIND_EVENT_FUNC(x) std::bind(&Application::x, this, std::placeholders::_1)

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdata();
		}
	}
	void Application::OnEvent(Event& e)
	{
		EventDisPatcher dispatcher(e);
		dispatcher.Dispatcher<WindowCloseEvent>(BIND_EVENT_FUNC(OnWindowClosed));

		PTA_CORE_TRACE("{0}", e.ToString());
	}
	bool Application::OnWindowClosed(WindowCloseEvent& evnet)
	{
		m_Running = false;
		return true;
	}
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FUNC(OnEvent));
	}
	Application::~Application()
	{
	}
}
