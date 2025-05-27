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
			m_OrthSize = 1.0f;
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


	//struct Transform
	//{
	//	glm::vec3 m_Position = { 0.0f,0.0f,0.0f };
	//	glm::vec3 m_Rotation = { 0.0f,0.0f,0.0f };
	//	glm::vec3 m_Scale = { 1.0f,1.0f,1.0f };


	//	static glm::mat4& GetModelMatrix(Transform& transform)
	//	{
	//		glm::mat4 translate = glm::translate(glm::mat4(1.0f), transform.m_Position);
	//		glm::mat4 scale = glm::scale(glm::mat4(1.0f), transform.m_Scale);

	//		glm::vec3 radians = glm::radians(transform.m_Rotation); // 角度 转 弧度
	//		glm::vec3 eulerAngles(radians); // 示例值（单位：弧度）
	//		glm::quat quaternion = glm::quat(eulerAngles); // 计算出四元数
	//		glm::mat4 rotate = glm::mat4_cast(quaternion); // 根据四元数得出旋转矩阵
	//		// 本地 to 世界
	//		return translate * rotate * scale;
	//	}
	//};
}