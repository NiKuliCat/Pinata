#pragma once
#include <glm/glm.hpp>

namespace Pinata {


	class Transform
	{


	public:
		Transform() = default;
		~Transform() = default;

		Transform(glm::vec3& position)
			:m_Position(position), m_Rotation({ 0.0f,0.0f,0.0f }), m_Scale({ 1.0f,1.0f,1.0f }){
			CaculateModelMatrix();
		}

		Transform(glm::vec3& position, glm::vec3& rotation)
			:m_Position(position), m_Rotation(rotation), m_Scale({ 1.0f,1.0f,1.0f }) {
			CaculateModelMatrix();
		}

		Transform(glm::vec3& position, glm::vec3& rotation, glm::vec3& scale)
			:m_Position(position), m_Rotation(rotation), m_Scale(scale){
			CaculateModelMatrix();
		}

	public:
		void SetPosition(const glm::vec3& position);
		void SetRotation(const glm::vec3& rotation);
		void SetScale(const glm::vec3& scale);

		 glm::vec3& GetPosition()	 { return m_Position; }
		const glm::vec3& GetRotation()	const { return m_Rotation; }
		const glm::vec3& GetScale()		const { return m_Scale; }

	public:
		const glm::mat4& GetModelMatrix() const { return m_ModelMatrix; }
		
	private:
		void CaculateModelMatrix();

	private:
		glm::vec3 m_Position = { 0.0f,0.0f,0.0f };
		glm::vec3 m_Rotation = { 0.0f,0.0f,0.0f };
		glm::vec3 m_Scale = { 1.0f,1.0f,1.0f };

		glm::mat4 m_ModelMatrix = glm::mat4(1.0f);


	};
}