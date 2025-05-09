#include "ptapch.h"
#include "OrthographicCamera.h"
#include <glm/gtc/matrix_transform.hpp>
namespace Pinata {
	OrthographicCamera::OrthographicCamera(float left, float right, float down, float top)
		:m_ProjectionMatrix(glm::ortho(left,right, down, top,-1.0f,1.0f)),m_ViewMatrix(1.0f),m_Position(0.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	void OrthographicCamera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		UpdataMatrix();
	}
	void OrthographicCamera::SetRotation(const float rotation)
	{
		m_Rotation = rotation;
		UpdataMatrix();
	}
	void OrthographicCamera::SetProjectionMatrix(float left, float right, float down, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, down, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	const glm::vec3& OrthographicCamera::TransformObject2View_Position(glm::vec3& position)
	{
		return   m_ViewMatrix * glm::vec4(position, 1.0f);
	}

	void OrthographicCamera::UpdataMatrix()
	{
		//得到相机 to 世界空间 的转化矩阵
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) 
								* glm::rotate(glm::mat4(1.0f),glm::radians( m_Rotation), glm::vec3(0, 0, 1));

		//求逆， 得到世界 to 相机空间 的转化矩阵
		m_ViewMatrix = glm::inverse(transform); 
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;

	}
}