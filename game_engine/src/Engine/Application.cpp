#include "gepch.h"
#include "Application.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Log.h"

namespace GameEngine {
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	void Application::Run() {
		//WindowResizeEvent e(1234, 12);
		//GE_TRACE(e.ToString());

		while (m_Running) {
			m_Window->OnUpdate();
		};
	}
}
