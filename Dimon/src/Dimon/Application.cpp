#include "dmpch.h"
#include "Application.h"

#include "Events/MouseEvent.h"
#include "Log.h"
#include <glad/glad.h>
#include "Platform/Vulkan/VulkanContext.h"
//#include "CoreInput.h"
namespace Dimon {

#define BIND_EVENT_FN_CALLBACK(x) std::bind(&Application::x,this,std::placeholders::_1)

	Application* Application::s_Instance = nullptr;
	
	Application::Application()
	{
		DM_CORE_ASSERT(s_Instance,"no exist")
		s_Instance = this;
		m_Window =  std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN_CALLBACK(OnEvent));


		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		//For Render
		//Vertex Array
		m_vertexArray.reset(VertexArray::Create());

		float vertices[7 * 3] = {
			0.5f,1.0f,0.0f,0.8f,0.2f,0.8f,1.0f,
			0.0f,0.0f,0.0f,0.2f,0.3f,0.8f,1.0f,
			1.0f,0.0f,0.0f,0.8f,0.8f,0.2f,1.0f
		};
		

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ShaderDataType::Float3,"a_Position"},
			{ShaderDataType::Float4,"a_Color"}
		};
		m_VertexBuffer->SetLayout(layout);
		

		m_vertexArray->AddVertexBuffer(m_VertexBuffer);

		unsigned int indices[3] = { 0,1,2 };
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_vertexArray->AddIndexBuffer(m_IndexBuffer);

		m_Shader.reset(new Shader("fist","fist"));
	}
	void Application::OnEvent(Event& e) {
		EventDispatcher dispacher(e);
		dispacher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN_CALLBACK(OnWindowClose));
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
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			
			m_vertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
			//glUseProgram(program);
			m_VertexBuffer->Bind();
			m_Shader->Bind();
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

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
}

