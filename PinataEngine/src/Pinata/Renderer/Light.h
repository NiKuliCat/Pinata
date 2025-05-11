#pragma once
#include <glm/glm.hpp>
namespace Pinata {

	enum class LightType
	{
		Direction,
		Point
	};

	struct LightData
	{
		glm::vec3 Position = { 0.0f,0.0f,0.0f };
		glm::vec3 Direction = { 0.0f,0.0f,1.0f };;
		LightType Type = LightType::Direction;

		LightData(glm::vec3& position,glm::vec3& direction,LightType& type)
			:Position(position),Direction(direction),Type(type)
		{

		}
	};

	class Light
	{
	public:
		static Ref<Light> Create(LightType& lightType, glm::vec3& position, glm::vec3& direction);

	};
}