#pragma once
#include <Pinata.h>
#include "imgui.h"
#include <glm/gtc/type_ptr.hpp>

#include <chrono>


#define PROFILE_SCOPE(name) Timer timer##__Line__(name,[&](ProfileResult profileResult){m_ProfileResults.push_back(profileResult);})
template<typename Fn>
class Timer
{
public:
	Timer(const char* name,Fn&& func)
		:m_Name(name),m_Stopped(false),m_Func(func)
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		if (!m_Stopped)
			Stop();

	}


	void Stop()
	{
		auto endTimePtr = std::chrono::high_resolution_clock::now();
		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePtr).time_since_epoch().count();

		m_Stopped = true;
		float duration = (end - start) * 0.001f ;
		//std::cout <<m_Name<< "    Duration: " << duration << "ms" << std::endl;
		m_Func({ m_Name,duration });
	}


private:
	const char* m_Name;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	bool m_Stopped;
	Fn m_Func;
};



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
		for (auto& profile : m_ProfileResults)
		{
			char label[50];
			strcpy(label, " %.3f ms  ");
			strcat(label, profile.name);

			ImGui::Text(label, profile.time);
		}

		m_ProfileResults.clear();
		ImGui::End();
	}

	virtual void OnAttach() override
	{
		
		Pinata::TextureAttributes attri;
		m_Texture2D_A = Pinata::Texture2D::Create(attri,"Assets/Textures/03.png");
		m_Texture2D_B = Pinata::Texture2D::Create(attri, "Assets/Textures/02.png");
		defaultWhiteTex = Pinata::Texture2D::DefaultTexture(Pinata::DefaultTexColor::Magenta);
	}

	virtual void OnUpdate(float daltaTime) override
	{
		PROFILE_SCOPE("TestLayer::OnUpdate");
		{
			PROFILE_SCOPE("CameraController::OnUpdate");
			m_CameraController.OnUpdate(daltaTime);	
		}

		Pinata::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f,1.0f });
		Pinata::RenderCommand::Clear();

		//2D render draw call
		{
			PROFILE_SCOPE("Renderer2D::BeginScene");
			Pinata::Renderer2D::BeginScene(m_CameraController.GetCamera());
		}
		{
			PROFILE_SCOPE("Renderer2D::DrawQuad");
			//Pinata::Renderer2D::DrawQuad(
			//	glm::vec3(0.5f, 0.2f, 0.1f),
			//	glm::vec3(0.0f, 0.0f, 0.0f), // 실똑
			//	glm::vec3(0.5f, 0.5f, 1.0f),
			//	tintColor,
			//	m_Texture2D_B
			//);
			Pinata::Renderer2D::DrawQuad(
				glm::vec3(0.5f, 1.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f), // 실똑
				glm::vec3(0.5f, 0.5f, 1.0f),
				tintColor,
				m_Texture2D_A
			);

			Pinata::Renderer2D::DrawQuad(
				glm::vec3(-0.5f, 0.0f, 0.1f),
				glm::vec3(0.0f, 0.0f, 0.0f), // 실똑
				glm::vec3(1.0f, 1.0f, 1.0f),
				tintColor
			);
		}

		Pinata::Renderer2D::EndScene();


	}

	virtual void OnEvent(Pinata::Event& event)
	{
		m_CameraController.OnEvent(event);
	}


private:
	Pinata::Ref<Pinata::Texture2D> m_Texture2D_A;
	Pinata::Ref<Pinata::Texture2D> m_Texture2D_B;
	Pinata::Ref<Pinata::Texture2D> defaultWhiteTex;
	glm::vec4 tintColor = {1.0f,1.0f,1.0f,1.0f};
	int intensity;

	Pinata::OrthoCameraController  m_CameraController;


	struct ProfileResult
	{
		const char* name;
		float time;
	};

	std::vector<ProfileResult> m_ProfileResults;

};