#include "ptapch.h"
#include "Pinata/Component/Transform.h"
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>
namespace Pinata {
	glm::mat4& Transform::GetModelMatrix(Transform& transform)
	{
		glm::mat4 translate = glm::translate(glm::mat4(1.0f), transform.Position);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), transform.Scale);

		glm::vec3 radians = glm::radians(transform.Rotation); // �Ƕ� ת ����
		glm::vec3 eulerAngles(radians); // ʾ��ֵ����λ�����ȣ�
		glm::quat quaternion = glm::quat(eulerAngles); // �������Ԫ��
		glm::mat4 rotate = glm::mat4_cast(quaternion); // ������Ԫ���ó���ת����
		// ���� to ����
		 return translate * scale;
	}
	const glm::mat4& Transform::GetLookAtMatrix(const Transform& transform)
	{
		glm::vec3 position = transform.Position;
		glm::vec3 rotation = transform.Rotation;
		glm::vec3 front, right;
		glm::vec3 up = { 0.0f,1.0f,0.0f };
		front.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
		front.y = sin(glm::radians(rotation.x));
		front.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
		front = glm::normalize(front);
		right = glm::normalize(glm::cross(front, up));
		up = glm::normalize(glm::cross(right, front));

///------------------------------------------------------------------------------------------//
///�˴�glm::lookAt ��Ч�� ����� GetViewMatrix
///���ʾ�������ռ�ת����ռ��ת������
///�ο� https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/camera.h 
/// lookAtʵ�� https://learnopengl.com/code_viewer.php?code=getting-started/camera-exercise2
///ע��ڶ����������ڲ���Ҫ����positionλ�ã���Ȼ�������
/// ----------------------------------------------------------------------------------------//
		glm::mat4 view = glm::lookAt(position,front, up);
		//glm::mat4 view = glm::lookAt(position, position + front, up); 
		return view;
	}

	const glm::mat4& Transform::GetViewMatrix(const Transform& transform)
	{
		glm::mat4 view = glm::translate(glm::mat4(1.0f), transform.Position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0, 0, 1));
		 return glm::inverse(view);
	}

}