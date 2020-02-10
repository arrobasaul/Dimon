#include "dmpch.h"
#include "Application.h"

#include "Events/MouseEvent.h"
#include "Log.h"
#include <GLFW/glfw3.h>
namespace Dimon {
#define BIND_EVENT_FN_CALLBACK(x) std::bind(&Application::x,this,std::placeholders::_1)
	Application::Application()
	{
		m_Window =  std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN_CALLBACK(OnEvent));
	}
	void Application::OnEvent(Event& e) {
		EventDispatcher dispacher(e);
		dispacher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN_CALLBACK(OnWindowClose));
		DM_CORE_INFO("{0}", e);
	}
	Application::~Application()
	{
	}
	
	void Application::Run()
	{
		/*WindowResizeEvent e(1280, 720);
		DM_CLIENT_TRACE(e);

		MouseMovedEvent f(3234.55f, 12413.56f);
		DM_CLIENT_ERROR(f);*/

		while (m_Running) {
			
			m_Window->OnUpdate();
		}
	}
	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}
}

