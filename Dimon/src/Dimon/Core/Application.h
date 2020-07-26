#pragma once
#include "Core.h"
#include "Window.h"
#include "Dimon/Layer/LeyerStack.h"
#include "Dimon/Events/Event.h"
#include "Dimon/Events/ApplicationEvent.h"
#include "Dimon/Layer/ImGui/ImGuiLayer.h"
#include "Dimon/Shaders/Shader.h"
#include "Dimon/Render/Buffer.h"
#include "Dimon/Render/VertexArray.h"
#include "Dimon/Render/OrthographicCamera.h"
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
		bool Application::OnWindowResize(WindowResizeEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true, m_Minimazed = false;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack  m_LayerStack;
		static Application* s_Instance;

		float m_LastFrameTime;
		
		//glm::vec3 CamaraPosition = { 1.0f, 1.0f, 1.0f };
	};
	Application* CreateApplication();
}


