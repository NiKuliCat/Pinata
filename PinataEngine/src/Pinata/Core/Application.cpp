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

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdata();
			}

			m_Window->OnUpdata();
		}
	}
	void Application::OnEvent(Event& e)
	{
		EventDisPatcher dispatcher(e);
		dispatcher.Dispatcher<WindowCloseEvent>(BIND_EVENT_FUNC(OnWindowClosed));

		PTA_CORE_TRACE("{0}", e.ToString());

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.m_Handled) 
				break;
		}
	}
#pragma region --------------------------------------Layer

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}
	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}
#pragma endregion

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
