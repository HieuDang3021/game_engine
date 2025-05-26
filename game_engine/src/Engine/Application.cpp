#include "gepch.h"
#include "Application.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Log.h"

namespace GameEngine {
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run() {
		WindowResizeEvent e(1234, 12);
		GE_TRACE(e.ToString());

		while (true);
	}
}
