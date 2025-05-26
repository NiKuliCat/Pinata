#include "ptapch.h"
#include "Pinata/Component/Transform.h"
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>
namespace Pinata {
	const glm::mat4& Transform::GetModelMatrix(const Transform& transform)
	{
		glm::mat4 translate = glm::translate(glm::mat4(1.0f), transform.Position);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), transform.Scale);

		float pitch = glm::radians(transform.Rotation.x);
		float yaw = glm::radians(transform.Rotation.y);
		float roll = glm::radians(transform.Rotation.z);
		glm::quat rotate_Quat = glm::yawPitchRoll(yaw, pitch, roll);
		rotate_Quat = glm::normalize(rotate_Quat);
		glm::mat4 rotation = glm::mat4(rotate_Quat);
		// 本地 to 世界
		 return translate * rotation *  scale;
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
///此处glm::lookAt 等效于 下面的 GetViewMatrix
///本质就是世界空间转相机空间的转化矩阵
///参考 https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/camera.h 
/// lookAt实现 https://learnopengl.com/code_viewer.php?code=getting-started/camera-exercise2
///注意第二个参数现在不需要加上position位置，不然结果出错
/// ----------------------------------------------------------------------------------------//
		glm::mat4 view = glm::lookAt(position,front, up);
		//glm::mat4 view = glm::lookAt(position, position + front, up); 
		return view;
	}

	const glm::mat4& Transform::GetViewMatrix(const Transform& transform)
	{
		glm::mat4 translate = glm::translate(glm::mat4(1.0f), transform.Position);
		float pitch = glm::radians(transform.Rotation.x);
		float yaw = glm::radians(transform.Rotation.y);
		float roll = glm::radians(transform.Rotation.z);
		glm::quat rotate_Quat = glm::yawPitchRoll(yaw, pitch, roll);
		rotate_Quat = glm::normalize(rotate_Quat);
		glm::mat4 rotation = glm::mat4(rotate_Quat);
		return glm::inverse(translate * rotation);
	}

}