#include "dmpch.h"
#include "Application.h"

#include "Dimon/Events/MouseEvent.h"
#include "Log.h"
#include <glad/glad.h>
#include "Dimon/Render/RendererCommand.h"
#include "Dimon/Render/Renderer.h"
//#include "Platform/Vulkan/VulkanContext.h"
#include "CoreInput.h"
#include "Dimon/Util/TimeStep.h"
#include <GLFW/glfw3.h>
namespace Dimon {

#define BIND_EVENT_FN_CALLBACK(x) std::bind(&Application::x,this,std::placeholders::_1)

	Application* Application::s_Instance = nullptr;
	
	Application::Application()
	{
		DM_CORE_ASSERT(s_Instance,"no exist")
		s_Instance = this;
		m_Window =  std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN_CALLBACK(OnEvent));
		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);		
	}
	void Application::OnEvent(Event& e) {
		EventDispatcher dispacher(e);
		dispacher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN_CALLBACK(OnWindowClose));
		dispacher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN_CALLBACK(OnWindowResize));
		//DM_CORE_INFO("{0}", e);
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
		WindowResizeEvent e(1280, 720);
		DM_CLIENT_TRACE(e);

		MouseMovedEvent f(3234.55f, 12413.56f);
		DM_CLIENT_ERROR(f);
		//auto program = loadShaders("basic", "basic");
		/*GLFWwindow* window2 = static_cast<GLFWwindow*>(m_Window->GetNativeWindow());
		VulkanContext contextVulkan(window2);

		contextVulkan.Run();*/

		while (m_Running) {
			//contextVulkan.drawFrame();
			float time = (float)glfwGetTime();
			TimeStep timeStep = time - m_LastFrameTime;
			m_LastFrameTime = time;
			if (!m_Minimazed) {
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(timeStep);
			}

			//auto [x, y] = CoreInput::GetMousePosition();
			m_ImGuiLayer->Begin();

			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();

			m_ImGuiLayer->End();

			//DM_CORE_TRACE("{0}-{1}",x,y);
			m_Window->OnUpdate();
		}
		//contextVulkan.cleanup();
	}
	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}
	bool Application::OnWindowResize(WindowResizeEvent& e) {
		if (e.GetHeight() == 0 || e.GetWidth() == 0) {
			m_Minimazed = true;
			return false;
		}
		m_Minimazed = false;
		Renderer::OnwindowsResized(e.GetWidth(), e.GetHeight());
		return true;
	}
}

