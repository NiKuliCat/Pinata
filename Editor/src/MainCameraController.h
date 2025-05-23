#pragma once
#include "Pinata.h"
#include "Pinata/Component/Component.h"
#include "Pinata/Scene/ScriptableObject.h"
namespace Pinata {
	class MainCameraController : public ScriptableObject
	{
	public:
		void OnCreate()
		{
			m_CameraTranslationSpeed = 1.0f;
		}

		void OnUpdate(float deltatime)
		{
			if (Input::IsKeyPressed(Key::A))
			{
				GetComponent<Transform>().Position.x -= m_CameraTranslationSpeed * deltatime;
			}
			if (Input::IsKeyPressed(Key::D))
			{
				GetComponent<Transform>().Position.x += m_CameraTranslationSpeed * deltatime;
			}
			if (Input::IsKeyPressed(Key::W))
			{
				GetComponent<Transform>().Position.y += m_CameraTranslationSpeed * deltatime;
			}
			if (Input::IsKeyPressed(Key::S))
			{
				GetComponent<Transform>().Position.y -= m_CameraTranslationSpeed * deltatime;
			}

		}
	private:
		float  m_CameraTranslationSpeed = 1.0f;
	};
}