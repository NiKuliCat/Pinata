#pragma once
#include "Pinata/Event/Event.h"
#include "Pinata/Event/MouseEvent.h"
#include <glm/glm.hpp>
namespace Pinata {

	class EditorCamera
	{
	public:
		EditorCamera() = default;
		EditorCamera(float fov,float aspect, float nearPlane, float farPlane);

		void OnUpdate(float deltaTime);
		void OnEvent(Event& event);

		inline float GetDistance() const { return m_Distance; }
		inline void SetDistance(const float value) { m_Distance = value; }

		inline void SetViewport(const float width, const float height) { m_ViewportWidth = width; m_ViewportHeight = height; UpdateProjectionMatrix(); }

		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		glm::mat4 GetViewProjectionMatrix() const { return m_ProjectionMatrix * m_ViewMatrix; }
		
		glm::vec3 GetUpDirection() const;
		glm::vec3 GetForwardDirection() const;
		glm::vec3 GetRightDirection() const;

		const glm::vec3& GetPosition() const { return m_Position; }

		glm::quat GetOrientation() const;

		float GetPitch() const { return m_Pitch; }
		float GetYaw() const { return m_Yaw; }
	private:
		void UpdateProjectionMatrix();
		void UpdateViewMatrix();

		bool OnMouseScroll(MouseScrolledEvent& event);

		void MousePan(const glm::vec2& delta);
		void MouseRotate(const glm::vec2& delta);
		void MouseZoom(float delta);

		glm::vec3 CalculatePosition() const;

		std::pair<float, float> PanSpeed() const;
		float RotationSpeed() const;
		float ZoomSpeed() const;

	private:
		float m_FOV = 45.0f, m_Aspect = 16.0f / 9.0f, m_Near = 0.1f , m_Far = 100.0f;

		glm::vec3 m_Position;
		glm::vec3 m_FocusPosition = { 0.0f,0.0f,0.0f };
		glm::vec2 m_MousePosition = { 0.0f,0.0f };

		float m_Distance = 10.0f;
		float m_Pitch = 0.0f, m_Yaw = 0.0f;

		float m_ViewportWidth = 1920.0f, m_ViewportHeight = 1080.0f;

		glm::mat4 m_ViewMatrix, m_ProjectionMatrix;

	};

}