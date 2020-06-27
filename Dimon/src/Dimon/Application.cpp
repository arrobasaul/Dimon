#include "dmpch.h"
#include "Application.h"

#include "Events/MouseEvent.h"
#include "Log.h"
#include <glad/glad.h>
#include "Render/RendererCommand.h"
#include "Render/Renderer.h"
//#include "Platform/Vulkan/VulkanContext.h"
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
		
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ShaderDataType::Float3,"a_Position"},
			{ShaderDataType::Float4,"a_Color"}
		};
		m_VertexBuffer->SetLayout(layout);
		m_vertexArray->AddVertexBuffer(m_VertexBuffer);

		unsigned int indices[3] = { 0,1,2 };
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_vertexArray->AddIndexBuffer(m_IndexBuffer);


		m_SquereVertexArray.reset(VertexArray::Create());
		float vertices2[3 * 4] = {
		   -0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		}; 

		std::shared_ptr<VertexBuffer> squereVB;
		squereVB.reset(VertexBuffer::Create(vertices2, sizeof(vertices2)));
		BufferLayout layout2 = {
			{ShaderDataType::Float3,"a_Position"}
		};
		squereVB->SetLayout(layout2);
		m_SquereVertexArray->AddVertexBuffer(squereVB);

		unsigned int indices2[6] = { 0, 1, 2, 0, 2, 3 };
		std::shared_ptr<IndexBuffer> squereIB;
		squereIB.reset(IndexBuffer::Create(indices2, sizeof(indices2) / sizeof(uint32_t)));
		m_SquereVertexArray->AddIndexBuffer(squereIB);

		m_Shader.reset(new Shader("fist","fist"));
		m_Shader2.reset(new Shader("fist2", "fist2"));
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
			glClear(GL_COLOR_BUFFER_BIT);
			
			RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });

			RendererCommand::Clear();

			Renderer::BeginScene();

			m_Shader2->Bind();
			Renderer::Submit(m_SquereVertexArray);

			m_Shader->Bind();
			Renderer::Submit(m_vertexArray);

			Renderer::EndScene();
			/*
			m_Shader2->Bind();
			m_SquereVertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_SquereVertexArray->GetIndexBuffers()->GetCount(), GL_UNSIGNED_INT, nullptr);


			m_Shader->Bind();
			m_vertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_vertexArray->GetIndexBuffers()->GetCount(), GL_UNSIGNED_INT, nullptr);
			*/
			//glUseProgram(program);
			//m_VertexBuffer->Bind();
			

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

