#pragma once

#include "Engine/Core.h"
#include "gepch.h"

namespace GameEngine {

	//Event is currently blocking type

	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, windowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyReleased, KeyPressed,
		MouseButtonPressed, MouseButtonRelease, MouseMoved, MouseScrolled
	};

	enum EventCategory {
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4),
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; } 

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class ENGINE_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); };

		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}


		inline bool Handled() { return m_Handled; }
	protected:
		bool m_Handled = false;
	};

	class EventDispatcher {
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event(event) {
		}

		template<typename T>
		bool Dispatch(EventFn<T> func) {
			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.ToString();
	}

	// Specialize fmt::formatter for Event types outside the GameEngine namespace
	template<typename T>
	struct fmt::formatter<
		T, std::enable_if_t<std::is_base_of<GameEngine::Event, T>::value, char>>
		: fmt::formatter<std::string>
	{
		auto format(const T& event, fmt::format_context& ctx) const
		{
			return fmt::format_to(ctx.out(), "{}", event.ToString());
		}
	};

	// Utility function for formatting strings with arguments
	template <typename... T>
	std::string StringFromArgs(fmt::format_string<T...> fmt, T&&... args)
	{
		return fmt::format(fmt, std::forward<T>(args)...);
	}
}