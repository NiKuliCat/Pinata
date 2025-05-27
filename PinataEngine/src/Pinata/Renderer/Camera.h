#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace Pinata {

	enum class ProjectionMode
	{
		Orthographic = 0,
		Perspective  = 1
	};

	class Camera
	{
	public:
		Camera();
		Camera(ProjectionMode mode, float fov, float aspect, float nearPlane, float farPlane);
		~Camera() = default;
	public:
		const glm::mat4& GetProjectionMatrix()const { return m_ProjectionMatrix; }
		void CaculateProjectionMatrix(ProjectionMode mode,float fov, float orthsize, float aspect, float nearPlane, float farPlane);

	private:
////欧拉角方式：传入相机坐标，以及欧拉角，旋转顺序，Y-X,忽略Z轴,https://learnopengl-cn.github.io/01%20Getting%20started/09%20Camera/#_9
		void CaculateViewMatrix(glm::vec3& position,glm::vec3& rotation); 

		//void CaculateMatrix(glm::vec3& position,glm::vec4& quaternion);


	private:
		ProjectionMode m_ProjectionMode = ProjectionMode::Orthographic;

////----  perspective properties ---------------------------//
		float m_FOV = 45.0f; // 控制缩放值， == zoomlevel
		float m_Aspect = 19.0f / 6.0f;
		float m_Near = 0.1f, m_Far = 100.0f;
////-------------------------------------------------------//

////----  orthographic properties ---------------------------//
		float m_OrthSize = 1.0f;
		float m_OrthNear = -1.0f;
		float m_OrthFar = 1.0f;
////-------------------------------------------------------//
		glm::mat4 m_ProjectionMatrix;
	};
}
