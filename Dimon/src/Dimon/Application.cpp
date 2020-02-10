#include "dmpch.h"
#include "Application.h"

#include "Events/MouseEvent.h"
#include "Log.h"
#include <GLAD/glad.h>
namespace Dimon {

#define BIND_EVENT_FN_CALLBACK(x) std::bind(&Application::x,this,std::placeholders::_1)

	Application* Application::s_Instance = nullptr;
	Application::Application()
	{
		DM_CORE_ASSERT(s_Instance,"no exist")
		s_Instance = this;
		m_Window =  std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN_CALLBACK(OnEvent));


	}
	void Application::OnEvent(Event& e) {
		EventDispatcher dispacher(e);
		dispacher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN_CALLBACK(OnWindowClose));
		DM_CORE_INFO("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}
	Application::~Application()
	{
	}
	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}
	void Application::Run()
	{
		/*WindowResizeEvent e(1280, 720);
		DM_CLIENT_TRACE(e);

		MouseMovedEvent f(3234.55f, 12413.56f);
		DM_CLIENT_ERROR(f);*/
		
		while (m_Running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}
	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}
}

