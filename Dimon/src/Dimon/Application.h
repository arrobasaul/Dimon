#pragma once
#include "Core.h"
#include "Window.h"
#include "Layer/LeyerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Dimon/Layer/ImGui/ImGuiLayer.h"
#include "Dimon/Shaders/Shader.h"
#include "Render/Buffer.h"
#include "Render/VertexArray.h"
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
		ImGuiLayer* m_ImGuiLayer;
		LayerStack  m_LayerStack;
		static Application* s_Instance;
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		std::shared_ptr<VertexArray> m_vertexArray;
	};
	Application* CreateApplication();
}


