#pragma once

#include "gepch.h"

#include "Engine/Core.h"
#include "Engine/Events/Event.h"

namespace GameEngine {

	//window properties
	struct WindowProps
	{
		std::string Title;
		unsigned int Height;
		unsigned int Width;

		WindowProps(const std::string& title = "Game Engine",
			unsigned int height = 720,
			unsigned int width = 1280)
			:Title(title), Height(height), Width(width){ }

	};

	// Interface representing a desktop system based window
	class ENGINE_API Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetHeight() const = 0;
		virtual unsigned int GetWidth() const = 0;

		//Window attribute
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}