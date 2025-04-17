#include "ptapch.h"
#include "Application.h"
#include "Pinata/Event/ApplicationEvent.h"
#include "Pinata/Core/Input.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
namespace Pinata {

	Application* Application::s_Instance = nullptr;
	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(m_VertexArray);

			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);


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

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);
		
		float vertexs[7 * 3] = {
			-0.5f, -0.5f, 0.0f,1.0f,0.0f,0.0f,1.0f,
			0.0f, 0.5f, 0.0f,0.0f,1.0f,0.0f,1.0f,
			0.5f, -0.5f, 0.0f,0.0f,0.0f,1.0f,1.0f
		};
		m_VertexBuffer.reset(VertexBuffer::Create(vertexs, sizeof(vertexs)));
		m_VertexBuffer->Bind();

		BufferLayout layout = {
			{ShaderDataType::Float3,"PositionOS"},
			{ShaderDataType::Float4,"Color"}
		};
		m_VertexBuffer->SetLayout(layout);

		uint32_t index = 0;
		for (auto& element : m_VertexBuffer->GetLayout())
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.Count, GL_FLOAT, GL_FALSE, layout.GetVertexStride(), (void*)element.Offset);
			index++;
		}

		//glEnableVertexAttribArray(0);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		uint32_t indexs[3] = { 0,1,2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indexs, 3));
		m_IndexBuffer->Bind();

		m_Shader = new OpenGLShader();
		m_Shader->Creat("F:\\dev\\PinataEngine\\PinataEngine\\src\\Platform\\OpenGL\\Shaders\\Basic.shader", 
			"F:\\dev\\PinataEngine\\PinataEngine\\src\\Platform\\OpenGL\\Shaders\\Basic.shader");
		//m_Shader->Creat("src/Pinata.h", "Shaders/Basic.shader");
		m_Shader->Register();
	}
	Application::~Application()
	{
	}
}
