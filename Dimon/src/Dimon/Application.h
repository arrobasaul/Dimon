#pragma once
#include "Core.h"
#include "Window.h"
#include "Layer/LeyerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

namespace Dimon {
	class DIMON_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);

		//for Layers
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		inline static Application& Get() {	return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		LayerStack  m_LayerStack;
		static Application* s_Instance;
	};
	Application* CreateApplication();
}


