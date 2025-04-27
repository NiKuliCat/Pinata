#pragma once
#include <Pinata.h>
#include "imgui.h"

class TestLayer : public Pinata::Layer
{
public:
	TestLayer() :Layer("Test")
	{
		m_Camera = new Pinata::OrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f);
		m_Camera->SetPosition({ 0.5f,0.5f,0.0f });
		//m_Camera->SetRotation(45.0f);
	}

	virtual void OnAttach() override
	{
		//triangle
		m_VertexArray.reset(Pinata::VertexArray::Create());
		float vertexs[7 * 3] = {
			-0.5f, -0.5f, 0.0f,1.0f,0.0f,0.0f,1.0f,
			0.0f, 0.5f, 0.0f,0.0f,1.0f,0.0f,1.0f,
			0.5f, -0.5f, 0.0f,0.0f,0.0f,1.0f,1.0f
		};
		m_VertexBuffer.reset(Pinata::VertexBuffer::Create(vertexs, sizeof(vertexs)));
		Pinata::BufferLayout layout = {
			{Pinata::ShaderDataType::Float3,"PositionOS"},
			{Pinata::ShaderDataType::Float4,"Color"}
		};
		m_VertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);


		uint32_t indexs[3] = { 0,1,2 };
		m_IndexBuffer.reset(Pinata::IndexBuffer::Create(indexs, 3));
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
		std::shared_ptr<Pinata::VertexBuffer> squareVB;
		std::shared_ptr<Pinata::IndexBuffer> squareIB;

		squareVA.reset(Pinata::VertexArray::Create());
		squareVB.reset(Pinata::VertexBuffer::Create(squarePos, sizeof(squarePos)));
		squareIB.reset(Pinata::IndexBuffer::Create(squareIndices, 6));
		squareVB->SetLayout(layout);
		squareVA->AddVertexBuffer(squareVB);
		squareVA->SetVertexBuffer(squareIB);

		m_Shader.reset(new Pinata::OpenGLShader());
		m_Shader->Creat("F:\\dev\\PinataEngine\\PinataEngine\\src\\Platform\\OpenGL\\Shaders\\Basic.shader",
			"F:\\dev\\PinataEngine\\PinataEngine\\src\\Platform\\OpenGL\\Shaders\\Basic.shader");
	}

	virtual void OnUpdata() override
	{
		Pinata::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f,1.0f });
		Pinata::RenderCommand::Clear();

		Pinata::Renderer::BeginScene(m_Camera);

		Pinata::Renderer::Submit(squareVA, m_Shader);
		Pinata::Renderer::Submit(m_VertexArray, m_Shader);

		Pinata::Renderer::EndScene();
	}

	virtual void OnEvent(Pinata::Event& event)
	{
		Pinata::EventDisPatcher dispatcher(event);
		dispatcher.Dispatcher<Pinata::KeyPressedEvent>(BIND_EVENT_FUNC(TestLayer::OnMouseScrolled));
	}

	bool OnMouseScrolled(Pinata::KeyPressedEvent& event)
	{
		glm::vec3 pos = m_Camera->GetPosition();
		if (event.GetKeyCode() == Pinata::Key::Up)
		{
			pos += glm::vec3(0.0, 0.1f, 0.0f);
		}
		if (event.GetKeyCode() == Pinata::Key::Down)
		{
			pos += glm::vec3(0.0, -0.1f, 0.0f);
		}
		if (event.GetKeyCode() == Pinata::Key::Left)
		{
			pos += glm::vec3(-0.1f, 0.0f, 0.0f);
		}
		if (event.GetKeyCode() == Pinata::Key::Right)
		{
			pos += glm::vec3(0.1f, 0.0f, 0.0f);
		}
			m_Camera->SetPosition(pos);

		PTA_INFO(event.ToString());
		return false;
	}


private:
	std::shared_ptr< Pinata::Shader> m_Shader;
	std::shared_ptr< Pinata::VertexBuffer> m_VertexBuffer;
	std::shared_ptr< Pinata::IndexBuffer> m_IndexBuffer;
	std::shared_ptr< Pinata::VertexArray> m_VertexArray;

	std::shared_ptr< Pinata::VertexArray> squareVA;

	Pinata::OrthographicCamera* m_Camera;


};