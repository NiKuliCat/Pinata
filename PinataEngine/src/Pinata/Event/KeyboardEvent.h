#pragma once
#include "Event.h"
#include "Pinata/Core/KeyCode.h"
namespace Pinata {

	class PINATA_API KeyboardEvent : public Event
	{
	public:
		KeyCode GetKeyCode()const { return m_KeyCode; }

		// " | " 按位与或运算， 有1则1，全0则0
		// EventKeyboard | EventInput means (EventKeyboard or EventInput)
		EVENT_CLASS_CATEGORY(EventKeyboard | EventInput )
		
	protected:
		KeyCode m_KeyCode;

		KeyboardEvent(const KeyCode keycode)
			:m_KeyCode(keycode){ }
	};

	class PINATA_API KeyPressedEvent : public KeyboardEvent
	{
	public:
		KeyPressedEvent(const KeyCode keycode,bool isRepeat = false)
			:KeyboardEvent(keycode),m_IsRepeat(isRepeat){ }

		bool IsRepeat() { return m_IsRepeat; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent:" << m_KeyCode << "(repeat = " << m_IsRepeat << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		bool m_IsRepeat;
	};



	class PINATA_API KeyReleasedEvent : public KeyboardEvent
	{
	public:
		KeyReleasedEvent(const KeyCode keycode)
			: KeyboardEvent(keycode) {
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};


	class PINATA_API KeyTypedEvent : public KeyboardEvent
	{
	public:
		KeyTypedEvent(const KeyCode keycode)
			: KeyboardEvent(keycode) {
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}