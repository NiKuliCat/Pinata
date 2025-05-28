#include "ptapch.h"
#include "Pinata/Component/Transform.h"
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>
namespace Pinata {

	const glm::mat4& Transform::GetModelMatrix(const Transform& transform)
	{
		glm::mat4 translate = glm::translate(glm::mat4(1.0f), transform.Position);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), transform.Scale);
		glm::mat4 rotate = glm::toMat4(glm::quat(glm::radians(transform.Rotation)));
		// 本地 to 世界
		 return translate * rotate *  scale;
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

	bool Transform::DecomposeTransformMatrix(const glm::mat4& transform, glm::vec3& out_Translation, glm::vec3& out_Rotation, glm::vec3& out_Scale)
	{
		using namespace glm;
		using T = float;

		mat4 LocalMatrix(transform);

		// Normalize the matrix.
		if (epsilonEqual(LocalMatrix[3][3], static_cast<float>(0), epsilon<T>()))
			return false;

		// First, isolate perspective.  This is the messiest.
		if (
			epsilonNotEqual(LocalMatrix[0][3], static_cast<T>(0), epsilon<T>()) ||
			epsilonNotEqual(LocalMatrix[1][3], static_cast<T>(0), epsilon<T>()) ||
			epsilonNotEqual(LocalMatrix[2][3], static_cast<T>(0), epsilon<T>()))
		{
			// Clear the perspective partition
			LocalMatrix[0][3] = LocalMatrix[1][3] = LocalMatrix[2][3] = static_cast<T>(0);
			LocalMatrix[3][3] = static_cast<T>(1);
		}

		// Next take care of translation (easy).
		out_Translation = vec3(LocalMatrix[3]);
		LocalMatrix[3] = vec4(0, 0, 0, LocalMatrix[3].w);

		vec3 Row[3], Pdum3;

		// Now get scale and shear.
		for (length_t i = 0; i < 3; ++i)
			for (length_t j = 0; j < 3; ++j)
				Row[i][j] = LocalMatrix[i][j];

		// Compute X scale factor and normalize first row.
		out_Scale.x = length(Row[0]);
		Row[0] = detail::scale(Row[0], static_cast<T>(1));
		out_Scale.y = length(Row[1]);
		Row[1] = detail::scale(Row[1], static_cast<T>(1));
		out_Scale.z = length(Row[2]);
		Row[2] = detail::scale(Row[2], static_cast<T>(1));

		// At this point, the matrix (in rows[]) is orthonormal.
		// Check for a coordinate system flip.  If the determinant
		// is -1, then negate the matrix and the scaling factors.
#if 0
		Pdum3 = cross(Row[1], Row[2]); // v3Cross(row[1], row[2], Pdum3);
		if (dot(Row[0], Pdum3) < 0)
		{
			for (length_t i = 0; i < 3; i++)
			{
				scale[i] *= static_cast<T>(-1);
				Row[i] *= static_cast<T>(-1);
			}
		}
#endif

		out_Rotation.y = asin(-Row[0][2]);
		if (cos(out_Rotation.y) != 0) {
			out_Rotation.x = atan2(Row[1][2], Row[2][2]);
			out_Rotation.z = atan2(Row[0][1], Row[0][0]);
		}
		else {
			out_Rotation.x = atan2(-Row[2][0], Row[1][1]);
			out_Rotation.z = 0;
		}

		/*out_Rotation.x = glm::degrees(out_Rotation.x);
		out_Rotation.y = glm::degrees(out_Rotation.y);
		out_Rotation.z = glm::degrees(out_Rotation.z);*/

		return true;
	}

}