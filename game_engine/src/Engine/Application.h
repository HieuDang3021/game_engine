#pragma once

#include "Core.h" 
#include "Events/Event.h"

namespace GameEngine {

	class ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//tobe define in client
	Application* CreateApplication();
}


