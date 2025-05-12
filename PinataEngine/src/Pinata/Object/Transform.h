#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>

namespace Pinata {
	struct Transform
	{
		glm::vec3 Position = { 0.0f,0.0f,0.0f };
		glm::vec3 Rotation = { 0.0f,0.0f,0.0f };
		glm::vec3 Scale = { 1.0f,1.0f,1.0f };

		Transform() = default;

		Transform(glm::vec3 position)
			:Position(position), Rotation({ 0.0f,0.0f,0.0f }), Scale({ 1.0f,1.0f,1.0f })
		{

		}

		Transform(glm::vec3 position, glm::vec3 rotation)
			:Position(position), Rotation(rotation), Scale({ 1.0f,1.0f,1.0f })
		{

		}

		Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
			:Position(position), Rotation(rotation), Scale(scale)
		{

		}
		static glm::mat4 GetModelMatrix(Transform& transform)
		{

			glm::mat4 translate = glm::translate(glm::mat4(1.0f), transform.Position);
			glm::mat4 scale = glm::scale(glm::mat4(1.0f), transform.Scale);

			glm::vec3 radians = glm::radians(transform.Rotation); // 角度 转 弧度
			glm::vec3 eulerAngles(radians); // 示例值（单位：弧度）
			glm::quat quaternion = glm::quat(eulerAngles); // 计算出四元数
			glm::mat4 rotate = glm::mat4_cast(quaternion); // 根据四元数得出旋转矩阵


			// 本地 to 世界
			glm::mat4 model = translate * rotate  * scale;

			return model;
		}
	};


}