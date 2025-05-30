#pragma once
#include "Event.h"
#include "Pinata/Core/MouseCode.h"
#include <sstream>
namespace Pinata {
	class PINATA_API MouseMovedEvent :public Event
	{
	public:
		MouseMovedEvent(const float x, const float y)
			:m_MouseX(x), m_MouseY(y) {
		}

		float GetX() const {return m_MouseX;}
		float GetY() const {return m_MouseY;}

		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventMouse | EventInput)

	private:
		float m_MouseX;
		float m_MouseY;
	};

	class PINATA_API MouseButtonEvent : public Event
	{
	public:
		MouseCode GetMouseButton() const { return m_MouseCode; }

		EVENT_CLASS_CATEGORY(EventMouse | EventInput |  EventMouseButton)

	protected:
		MouseButtonEvent(const MouseCode mousecode)
			:m_MouseCode(mousecode) {}

		MouseCode m_MouseCode;
	};


	class PINATA_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(const MouseCode mousecode)
			: MouseButtonEvent(mousecode) {
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_MouseCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class PINATA_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(const MouseCode mousecode)
			: MouseButtonEvent(mousecode) {
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_MouseCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};


	class PINATA_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(const float xOffset, const float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {
		}

		float GetXOffset() const { return m_XOffset; }
		float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventMouse | EventInput)
	private:
		float m_XOffset, m_YOffset;
	};
}