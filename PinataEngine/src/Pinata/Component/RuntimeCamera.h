#pragma once
#include "Pinata/Renderer/Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>

namespace Pinata {
	struct RuntimeCamera {
		Camera m_Camera;
		ProjectionMode m_ProjectionMode = ProjectionMode::Perspective;

		float m_FOV;
		float m_OrthSize;
		float m_Aspect;
		float m_Near, m_Far;
		float m_OrthNear, m_OrthFar;
		int m_Sort;
		
		RuntimeCamera()
		{
			m_Camera = Camera();
			m_ProjectionMode = ProjectionMode::Perspective;
			m_FOV = 45.0f;
			m_OrthSize = 4.0f;
			m_Aspect = 19.0f / 6.0f;
			m_Near = 0.1f;
			m_Far = 100.0f;
			m_OrthNear = -1.0f;
			m_OrthFar = 1.0f;
			m_Sort = 0;
			OnDataChange();
		}
		void OnDataChange()
		{
			m_Camera.CaculateProjectionMatrix(m_ProjectionMode, m_FOV, m_OrthSize, m_Aspect, m_Near, m_Far);
		}
	};
}