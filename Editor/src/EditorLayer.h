#pragma once
#include <Pinata.h>
#include <ImGui/imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <chrono>
#include "ImGuiPanel/SceneHierarchyPanel.h"
#include "Pinata/Editor/EditorCamera.h"
#define PROFILE_SCOPE(name) Timer timer##__Line__(name,[&](ProfileResult profileResult){m_ProfileResults.push_back(profileResult);})
template<typename Fn>
class Timer
{
public:
	Timer(const char* name, Fn&& func)
		:m_Name(name), m_Stopped(false), m_Func(func)
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
		float duration = (end - start) * 0.001f;
		//std::cout <<m_Name<< "    Duration: " << duration << "ms" << std::endl;
		m_Func({ m_Name,duration });
	}


private:
	const char* m_Name;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	bool m_Stopped;
	Fn m_Func;
};

namespace Pinata {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer()
			: Layer("Pinata Editor")
		{
		}
		virtual ~EditorLayer() = default;
		virtual void OnImGuiRender() override;

		virtual void OnAttach() override;

		virtual void OnUpdate(float daltaTime) override;

		virtual void OnEvent(Event& event) override;

	private:
		bool OnKeyPressed(KeyPressedEvent& event);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& event);

		void TryGetMousePickkingObject();


	private:
		Ref<Texture2D> m_Texture2D_A;
		Ref<Texture2D> m_Texture2D_B;
		Ref<Texture2D> defaultWhiteTex;

		Ref<Shader> m_Shader;
		Ref<Material> m_Material_A;
		Ref<Material> m_Material_B;

		Transform m_Transform_A;
		Transform m_Transform_B;

		Ref<Scene> m_Scene;
		EditorCamera m_EditorCamera;
		bool m_HasActiveScene = false;
		Object m_ScneneCamera;
		Ref<FrameBuffer> m_FrameBuffer;
		glm::vec2 m_ViewportSize;
		glm::vec2 m_ViewportBounds[2];
		float m_TimeStep;
		Object m_QuadObject;

		SceneHierarchyPanel m_HierarchyPanel;
		int32_t m_GizmoControlType = -1;

		struct ProfileResult
		{
			const char* name;
			float time;
		};
		std::vector<ProfileResult> m_ProfileResults;

	};

}