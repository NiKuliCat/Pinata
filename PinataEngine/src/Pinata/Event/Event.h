#pragma once
#include "ptapch.h"
#include "Pinata/Core/Core.h"
namespace Pinata {

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventApplication	= BIT(0),
		EventInput			= BIT(1),
		EventKeyboard		= BIT(2),
		EventMouse			= BIT(3),
		EventMouseButton	= BIT(4)

	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::type;}\
								virtual EventType GetEventType() const override { return GetStaticType();}\
								virtual const char* GetName() const override {return #type;}

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }


	class PINATA_API Event
	{
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }

		bool m_Handled = false;
	};

	class EventDisPatcher
	{
	public:
		EventDisPatcher(Event& event)
			:m_Event(event){ }


		template<typename T,typename F>
		bool Dispatcher(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled |= func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}


}


