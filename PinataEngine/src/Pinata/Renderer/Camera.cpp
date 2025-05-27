#include "ptapch.h"
#include "Camera.h"

namespace Pinata {
	Camera::Camera()
	{
		m_ProjectionMode = ProjectionMode::Perspective;
////----  perspective properties ---------------------------//
		m_FOV = 45.0f;
		m_Aspect = 19.0f / 6.0f;
		m_Near = 0.1f;
		m_Far = 100.0f;
////-------------------------------------------------------//

////-------------------------------------------------------//
		m_OrthSize = 1.0f;
		m_OrthNear = -1.0f;
		m_OrthFar = 1.0f;
////-------------------------------------------------------//
		
		m_ProjectionMatrix = glm::mat4(1.0f);
		CaculateProjectionMatrix(m_ProjectionMode, m_FOV, m_OrthSize, m_Aspect, m_Near, m_Far);
	}
	Camera::Camera(ProjectionMode mode, float fov, float aspect, float nearPlane, float farPlane)
		:m_FOV(fov),m_Aspect(aspect),m_Near(nearPlane),m_Far(farPlane)
	{
		CaculateProjectionMatrix(m_ProjectionMode,m_FOV, m_OrthSize, m_Aspect, m_Near, m_Far);
	}
	void Camera::CaculateViewMatrix(glm::vec3& position, glm::vec3& rotation)
	{
		float pitch = rotation.x;
		float yaw = rotation.y;
		glm::vec3 front, right;
		glm::vec3 up = { 0.0f,1.0f,0.0f };
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

		front = glm::normalize(front);
		right = glm::normalize(glm::cross(front, up));
		up = glm::normalize(glm::cross(right, front));
	}
	void Camera::CaculateProjectionMatrix(ProjectionMode mode, float fov, float orthsize,float aspect, float nearPlane, float farPlane)
	{
		m_ProjectionMode = mode;
		m_FOV = fov;
		m_Aspect = aspect;
		m_OrthSize = orthsize;
		
		if (m_ProjectionMode == ProjectionMode::Perspective)
		{
			m_Near = nearPlane;
			m_Far = farPlane;
			m_ProjectionMatrix= glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
		}
		else
		{
			m_OrthNear = nearPlane;
			m_OrthFar = farPlane;
			float w = m_Aspect * orthsize;
			float h = orthsize;
			m_ProjectionMatrix = glm::ortho(- w , w ,  - h, h , nearPlane, farPlane);
		}
	}
}