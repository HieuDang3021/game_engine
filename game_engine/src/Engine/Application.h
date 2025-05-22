#pragma once

#include "Core.h" 

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


