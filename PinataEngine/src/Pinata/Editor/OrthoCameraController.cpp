#include "ptapch.h"

#include "OrthoCameraController.h"
#include "Pinata/Core/Input.h"
#include "Pinata/Core/KeyCode.h"
namespace Pinata {

	OrthoCameraController::OrthoCameraController(float aspect, float zoomLevel,bool enableRotate)
		:m_Aspect(aspect),m_ZoomLevel(zoomLevel),m_Rotate(enableRotate),
		m_Camera(- aspect * zoomLevel,  aspect* zoomLevel,-zoomLevel, zoomLevel)
	{
		m_CameraTranslationSpeed = 1.0f * abs(zoomLevel);
	}

	OrthoCameraController::OrthoCameraController(float aspect, bool enableRotate)
		:OrthoCameraController(aspect,1.0f,enableRotate)
	{

	}

	void OrthoCameraController::OnUpdate(float daltaTime)
	{
		if (Input::IsKeyPressed(Key::A))
		{
			m_CameraPosition.x -= m_CameraTranslationSpeed * daltaTime;
		}
		if (Input::IsKeyPressed(Key::D))	
		{
			m_CameraPosition.x += m_CameraTranslationSpeed * daltaTime;
		}
		if (Input::IsKeyPressed(Key::W))
		{
			m_CameraPosition.y += m_CameraTranslationSpeed * daltaTime;
		}
		if (Input::IsKeyPressed(Key::S))
		{
			m_CameraPosition.y -= m_CameraTranslationSpeed * daltaTime;
		}

		m_Camera.SetPosition(m_CameraPosition);

		if (m_Rotate)
		{
			if (Input::IsKeyPressed(Key::Q))
			{
				m_CameraRotation -= m_CameraRotateSpeed * daltaTime;
			}
			if (Input::IsKeyPressed(Key::E))
			{
				m_CameraRotation += m_CameraRotateSpeed * daltaTime;
			}
			m_Camera.SetRotation(m_CameraRotation);
		}
	}

	void OrthoCameraController::OnEvent(Event& event)
	{
		EventDisPatcher dispatcher(event);
		dispatcher.Dispatcher<MouseScrolledEvent>(BIND_EVENT_FUNC(OrthoCameraController::OnMouseScrolled));
		//dispatcher.Dispatcher<WindowResizeEvent>(BIND_EVENT_FUNC(OrthoCameraController::OnWindowResize)); //更改成viewport窗户显示后,不跟踪主窗口的尺寸变化
	}

	void OrthoCameraController::OnResize(float width, float height)
	{
		m_Aspect = width / height;
		m_Camera.SetProjectionMatrix(-m_Aspect * m_ZoomLevel, m_Aspect * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

	
	bool OrthoCameraController::OnMouseScrolled(MouseScrolledEvent& event)
	{
		m_ZoomLevel -= event.GetYOffset() * 0.1f;
		m_CameraTranslationSpeed = 1.0f * abs(m_ZoomLevel);
		m_Camera.SetProjectionMatrix(-m_Aspect * m_ZoomLevel, m_Aspect * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthoCameraController::OnWindowResize(WindowResizeEvent& event)
	{
		OnResize((float)event.GetWidth(), (float)event.GetHeight());
		return false;
	}


}