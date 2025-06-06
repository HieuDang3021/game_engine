#pragma once

#include "Engine/Window.h"
#include <GLFW/glfw3.h>

namespace GameEngine {
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetHeight() const override { return m_Data.Height; };
		inline unsigned int GetWidth() const override { return m_Data.Width; };

		//window attribute
		inline void SetEventCallback(const EventCallbackFn& callback) override {
			m_Data.EventCallback = callback;
		};
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;

		struct WindowData {
			std::string Title;
			unsigned int Height, Width;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}

