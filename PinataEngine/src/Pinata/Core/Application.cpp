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

			squareVA->Bind();
			glDrawElements(GL_TRIANGLES, squareVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
			m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);


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

		//triangle
		m_VertexArray.reset(VertexArray::Create());
		float vertexs[7 * 3] = {
			-0.5f, -0.5f, 0.0f,1.0f,0.0f,0.0f,1.0f,
			0.0f, 0.5f, 0.0f,0.0f,1.0f,0.0f,1.0f,
			0.5f, -0.5f, 0.0f,0.0f,0.0f,1.0f,1.0f
		};
		m_VertexBuffer.reset(VertexBuffer::Create(vertexs, sizeof(vertexs)));
		BufferLayout layout = {
			{ShaderDataType::Float3,"PositionOS"},
			{ShaderDataType::Float4,"Color"}
		};
		m_VertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);


		uint32_t indexs[3] = { 0,1,2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indexs, 3));
		m_VertexArray->SetVertexBuffer(m_IndexBuffer);


		//square
		float squarePos[7 * 4] =
		{
			-0.8f, 0.8f, 0.0f,1.0f,1.0f,1.0f,1.0f,
			0.8f, 0.8f, 0.0f,0.0f,0.0f,0.0f,1.0f,
			0.8f, -0.8f, 0.0f,0.0f,0.0f,0.0f,1.0f,
			-0.8f, -0.8f, 0.0f,1.0f,1.0f,1.0f,1.0f
		};
		uint32_t squareIndices[6] = { 0,1,2,0,2,3 };
		std::shared_ptr<VertexBuffer> squareVB;
		std::shared_ptr<IndexBuffer> squareIB;

		squareVA.reset(VertexArray::Create());
		squareVB.reset(VertexBuffer::Create(squarePos,sizeof(squarePos)));
		squareIB.reset(IndexBuffer::Create(squareIndices, 6));
		squareVB->SetLayout(layout);//顶点布局同上
		squareVA->AddVertexBuffer(squareVB);
		squareVA->SetVertexBuffer(squareIB);

		m_Shader.reset(new OpenGLShader());
		m_Shader->Creat("F:\\dev\\PinataEngine\\PinataEngine\\src\\Platform\\OpenGL\\Shaders\\Basic.shader", 
			"F:\\dev\\PinataEngine\\PinataEngine\\src\\Platform\\OpenGL\\Shaders\\Basic.shader");
		m_Shader->Register();
	}
	Application::~Application()
	{
	}
}
