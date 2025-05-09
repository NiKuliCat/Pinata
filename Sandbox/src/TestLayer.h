#pragma once
#include <Pinata.h>
#include "imgui.h"
#include <glm/gtc/type_ptr.hpp>
class TestLayer : public Pinata::Layer
{
public:
	TestLayer() 
		: Layer("Test"), m_CameraController(16.0f / 9.0f,true),intensity(1)
	{
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Setting");
		ImGui::ColorEdit4("TintColor", glm::value_ptr(tintColor));
		ImGui::SliderInt("Intensity", &intensity, 0, 2);
		ImGui::End();
	}

	virtual void OnAttach() override
	{
		//triangle
		m_VertexArray = Pinata::VertexArray::Create();
		float vertexs[9 * 3] = {
			-0.5f, -0.5f, 0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,
			0.0f, 0.5f, 0.0f,0.0f,1.0f,0.0f,1.0f,0.5f,0.5f,
			0.5f, -0.5f, 0.0f,0.0f,0.0f,1.0f,1.0f,0.0f,1.0f
		};
		m_VertexBuffer = Pinata::VertexBuffer::Create(vertexs, sizeof(vertexs));
		Pinata::BufferLayout layout = {
			{Pinata::ShaderDataType::Float3,"PositionOS"},
			{Pinata::ShaderDataType::Float4,"Color"},
			{Pinata::ShaderDataType::Float2,"Texcoord"}
		};
		m_VertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);


		uint32_t indexs[3] = { 0,1,2 };
		m_IndexBuffer = Pinata::IndexBuffer::Create(indexs, 3);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);


		//square
		float squarePos[9 * 4] =
		{
			//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,1.0f,   1.0f, 1.0f,   // 右上
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,1.0f,   1.0f, 0.0f,   // 右下
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,1.0f,   0.0f, 0.0f,   // 左下
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,1.0f,   0.0f, 1.0f    // 左上
		};
		uint32_t squareIndices[6] = { 0, 1, 3, 1, 2, 3 };
		Pinata::Ref<Pinata::VertexBuffer> squareVB;
		Pinata::Ref<Pinata::IndexBuffer> squareIB;

		squareVA = Pinata::VertexArray::Create();
		squareVB = Pinata::VertexBuffer::Create(squarePos, sizeof(squarePos));
		squareIB = Pinata::IndexBuffer::Create(squareIndices, 6);
		squareVB->SetLayout(layout);
		squareVA->AddVertexBuffer(squareVB);
		squareVA->SetIndexBuffer(squareIB);

		m_Shader = Pinata::Shader::Creat("Assets/Shader/DefaultShader.shader"); // 更新shader读取
		Pinata::TextureAttributes attri;
		m_Texture2D = Pinata::Texture2D::Create(attri,"Assets/Textures/02.png");
		m_Shader->Bind();
		m_Texture2D->Bind(1);
		m_Shader->SetInt("_MainTex", 1);
	}

	virtual void OnUpdata(float daltaTime) override
	{
		m_CameraController.OnUpdate(daltaTime);
		//PTA_INFO("timeStep:{0}s({1}ms) per frame", Pinata::Time::GetDeltaTime(), Pinata::Time::GetDeltaTime() * 1000.0f);
		Pinata::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f,1.0f });
		Pinata::RenderCommand::Clear();

		//Pinata::Renderer::BeginScene(m_CameraController.GetCamera());

		//m_Shader->SetColor("_BaseColor", tintColor);
		//m_Shader->SetInt("_Intensity", intensity);
		//m_Texture2D->Bind();

		//Pinata::Renderer::Submit(squareVA, m_Shader);
		//Pinata::Renderer::Submit(m_VertexArray, m_Shader);

		//Pinata::Renderer::EndScene();


		//2D render draw call
		Pinata::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Pinata::Renderer2D::DrawQuad(
			glm::vec3(0.0f,0.0f,0.0f),
			glm::vec3(0.0f,0.0f,180.0f), // 角度
			glm::vec3(1.0f,1.0f,1.0f),
			tintColor,
			m_Texture2D
		);

		Pinata::Renderer2D::EndScene();


	}

	virtual void OnEvent(Pinata::Event& event)
	{
		m_CameraController.OnEvent(event);
	}


private:
	Pinata::Ref< Pinata::Shader> m_Shader;
	Pinata::Ref<Pinata::Texture2D> m_Texture2D;
	Pinata::Ref< Pinata::VertexBuffer> m_VertexBuffer;
	Pinata::Ref< Pinata::IndexBuffer> m_IndexBuffer;
	Pinata::Ref< Pinata::VertexArray> m_VertexArray;

	Pinata::Ref< Pinata::VertexArray> squareVA;

	glm::vec4 tintColor = {1.0f,1.0f,1.0f,1.0f};
	int intensity;

	Pinata::OrthoCameraController  m_CameraController;


};