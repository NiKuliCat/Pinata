#include "ptapch.h"
#include "Application.h"
#include "Pinata/Event/ApplicationEvent.h"
#include "Pinata/Core/Input.h"
#include <GLFW/glfw3.h>
namespace Pinata {

	Application* Application::s_Instance = nullptr;
	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);


			//执行所有layer的事件
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdata();
			}

			//执行所有layer的渲染程序
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();


			m_Window->OnUpdata();
		}
	}
	void Application::OnEvent(Event& e)
	{
		EventDisPatcher dispatcher(e);
		dispatcher.Dispatcher<WindowCloseEvent>(BIND_EVENT_FUNC(Application::OnWindowClosed));

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
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}
#pragma endregion

	bool Application::OnWindowClosed(WindowCloseEvent& evnet)
	{
		m_Running = false;
		return true;
	}
	Application::Application()
	{
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FUNC(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}
	Application::~Application()
	{
	}
}
