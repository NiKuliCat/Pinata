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
			if (Input::IsKeyPressed(Key::KPSubtract))
			{
				auto& cam = GetComponent<RuntimeCamera>();
				cam.m_FOV += m_ZoomLevelSpeed * deltatime;
				cam.OnDataChange();
			}
			if (Input::IsKeyPressed(Key::KPAdd))
			{
				auto& cam = GetComponent<RuntimeCamera>();
				cam.m_FOV -= m_ZoomLevelSpeed * deltatime;
				cam.OnDataChange();
			}
			if (Input::IsKeyPressed(Key::Q))
			{
				GetComponent<Transform>().Rotation.y -= m_CameraRotateSpeed * deltatime;
			}
			if (Input::IsKeyPressed(Key::E))
			{
				GetComponent<Transform>().Rotation.y += m_CameraRotateSpeed * deltatime;
			}
		}
	private:
		float  m_CameraTranslationSpeed = 1.0f;
		float  m_CameraRotateSpeed = 30.0f;
		float  m_ZoomLevelSpeed = 20.0f;
	};
}