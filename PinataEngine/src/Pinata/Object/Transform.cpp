#include "ptapch.h"
#include "Pinata/Object/Transform.h"
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>
namespace Pinata {
	void Transform::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		CaculateModelMatrix();
	}
	void Transform::SetRotation(const glm::vec3& rotation)
	{
		m_Rotation = rotation;
		CaculateModelMatrix();
	}
	void Transform::SetScale(const glm::vec3& scale)
	{
		m_Scale = scale;
		CaculateModelMatrix();
	}

	void Transform::CaculateModelMatrix()
	{
		glm::mat4 translate = glm::translate(glm::mat4(1.0f), m_Position);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), m_Scale);

		glm::vec3 radians = glm::radians(m_Rotation); // �Ƕ� ת ����
		glm::vec3 eulerAngles(radians); // ʾ��ֵ����λ�����ȣ�
		glm::quat quaternion = glm::quat(eulerAngles); // �������Ԫ��
		glm::mat4 rotate = glm::mat4_cast(quaternion); // ������Ԫ���ó���ת����
		// ���� to ����
		m_ModelMatrix = translate * rotate * scale;
	}
}