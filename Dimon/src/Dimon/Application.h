#pragma once
#include "Core.h"
namespace Dimon {
	class DIMON_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		
	};
	Application* CreateApplication();
}


