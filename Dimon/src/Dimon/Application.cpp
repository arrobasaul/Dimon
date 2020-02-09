#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Log.h"
namespace Dimon {
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		DM_CLIENT_TRACE(e);

		MouseMovedEvent f(100.5f, 200.5f);
		DM_CLIENT_TRACE(f);

		while (true);
	}
}

