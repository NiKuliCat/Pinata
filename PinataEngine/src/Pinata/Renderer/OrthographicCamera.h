#pragma once
#include <glm/glm.hpp>

namespace Pinata {

	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float top, float down);

		void SetPosition(const glm::vec3& position);
		const glm::vec3 GetPosition() const  { return m_Position; }
		void SetRotation(const float rotation);
		const float GetRotation() const { return m_Rotation; }

		const glm::mat4& GetProjectionMatrix()const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix()const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix()const { return m_ViewProjectionMatrix; }

	public:
		const glm::vec3&  TransformObject2View_Position(glm::vec3& position);

	private:
		void UpdataMatrix();
		
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position;
		float m_Rotation = 0.0f;
	};
}