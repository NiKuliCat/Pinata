#pragma once
#include <glm/glm.hpp>

namespace Pinata {


	struct Transform
	{

		glm::vec3 Position = { 0.0f,0.0f,0.0f };
		glm::vec3 Rotation = { 0.0f,0.0f,0.0f };
		glm::vec3 Scale = { 1.0f,1.0f,1.0f };

		Transform() = default;
		Transform(const Transform&) = default;
		~Transform() = default;

		Transform(glm::vec3& position)
			:Position(position), Rotation({ 0.0f,0.0f,0.0f }), Scale({ 1.0f,1.0f,1.0f }){}

		Transform(glm::vec3& position, glm::vec3& rotation)
			:Position(position), Rotation(rotation), Scale({ 1.0f,1.0f,1.0f }) {}

		Transform(glm::vec3& position, glm::vec3& rotation, glm::vec3& scale)
			:Position(position), Rotation(rotation), Scale(scale){}

		static const glm::mat4& GetModelMatrix(const Transform& transform);
		static const glm::mat4& GetLookAtMatrix(const Transform& transform);
		static const glm::mat4& GetViewMatrix(const Transform& transform);
	};
}