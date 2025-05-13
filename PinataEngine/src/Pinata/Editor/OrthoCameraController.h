#pragma once
#include "Pinata/Renderer/OrthographicCamera.h"
#include "Pinata/Event/MouseEvent.h"
#include "Pinata/Event/ApplicationEvent.h"
namespace Pinata {


	class OrthoCameraController
	{
	public:
		OrthoCameraController(float aspect, float zoomLevel = 1.0f,bool enableRotate = false);
		OrthoCameraController(float aspect, bool enableRotate = false);
		void OnUpdate(float daltaTime);

		void OnEvent(Event& event);
		void OnResize(float width, float height);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return  m_Camera; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& event);
		bool OnWindowResize(WindowResizeEvent& event);
	private:
		OrthographicCamera m_Camera;
		float m_Aspect; 
		float m_ZoomLevel;
		bool m_Rotate;

	private:
		glm::vec3 m_CameraPosition = { 0.0f,0.0f,0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 1.0f;
		float m_CameraRotateSpeed = 100.0f;

	};
}