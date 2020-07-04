#include <Dimon.h>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "ImGui/imgui.h"
#include <glm/gtc/type_ptr.hpp>
class ExampleLeyer : public Dimon::Layer {
public:
	ExampleLeyer()
		: Layer("Minecraf"), m_Camera(-1.0f, 1.0f, -1.0f, 1.0f) , CameraProsition(0)
	{
		m_vertexArray.reset(Dimon::VertexArray::Create());
		float vertices[7 * 3] = {
			0.5f,1.0f,0.0f,0.8f,0.2f,0.8f,1.0f,
			0.0f,0.0f,0.0f,0.2f,0.3f,0.8f,1.0f,
			1.0f,0.0f,0.0f,0.8f,0.8f,0.2f,1.0f
		};

		Dimon::Ref<Dimon::VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(Dimon::VertexBuffer::Create(vertices, sizeof(vertices)));
		Dimon::BufferLayout layout = {
			{Dimon::ShaderDataType::Float3,"a_Position"},
			{Dimon::ShaderDataType::Float4,"a_Color"}
		};
		m_VertexBuffer->SetLayout(layout);
		m_vertexArray->AddVertexBuffer(m_VertexBuffer);

		unsigned int indices[3] = { 0,1,2 };
		Dimon::Ref<Dimon::IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(Dimon::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_vertexArray->AddIndexBuffer(m_IndexBuffer);


		m_SquereVertexArray.reset(Dimon::VertexArray::Create());
		float vertices2[5 * 4] = {
		   -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		   -0.5f,  0.5f, 0.0f, 0.0f, 1.0f 
		};

		Dimon::Ref<Dimon::VertexBuffer> squereVB;
		squereVB.reset(Dimon::VertexBuffer::Create(vertices2, sizeof(vertices2)));
		Dimon::BufferLayout layout2 = {
			{Dimon::ShaderDataType::Float3,"a_Position"},
			{Dimon::ShaderDataType::Float2,"a_TextCoord"}
		};
		squereVB->SetLayout(layout2);
		m_SquereVertexArray->AddVertexBuffer(squereVB);

		unsigned int indices2[6] = { 0, 1, 2, 2, 3, 0 };
		Dimon::Ref<Dimon::IndexBuffer> squereIB;
		squereIB.reset(Dimon::IndexBuffer::Create(indices2, sizeof(indices2) / sizeof(uint32_t)));
		m_SquereVertexArray->AddIndexBuffer(squereIB);
		
		m_Shader = Dimon::Shader::Create("fist","Resources/Shaders/fist.vert", "Resources/Shaders/fist.frag");
		m_Shader2 = Dimon::Shader::Create("fist2", "Resources/Shaders/fist2.vert", "Resources/Shaders/fist2.frag");
		auto textureShader = m_ShaderLibrary.Load("TextShaderImage", "Resources/Shaders/TextShader.vert", "Resources/Shaders/TextShader.frag");

		m_Texture=  Dimon::Texture2D::Create("Resources/Texture/Checkerboard.png");
		m_ChernoTexture = Dimon::Texture2D::Create("Resources/Texture/saul.jpg");

		std::dynamic_pointer_cast<Dimon::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Dimon::OpenGLShader>(textureShader)->SetUniformInt("u_Texture", 0);
	}
	void OnUpdate(Dimon::TimeStep timeStep) override {
		DM_CORE_TRACE("Delta Time {0} ", timeStep.GetSeconds());

		if (Dimon::CoreInput::IsKeyPressed(DM_KEY_A)) {
			CameraProsition.x -= CameraMoveSpeed * timeStep;
		}
		else if (Dimon::CoreInput::IsKeyPressed(DM_KEY_D)) {
			CameraProsition.x += CameraMoveSpeed * timeStep;
		}

		if (Dimon::CoreInput::IsKeyPressed(DM_KEY_W)) {
			CameraProsition.y += CameraMoveSpeed * timeStep;
		}
		else if (Dimon::CoreInput::IsKeyPressed(DM_KEY_S)) {
			CameraProsition.y -= CameraMoveSpeed * timeStep;
		}

		if (Dimon::CoreInput::IsKeyPressed(DM_KEY_Q)) {
			m_CameraRotate += CameraMoveRotate * timeStep;
		}
		else if (Dimon::CoreInput::IsKeyPressed(DM_KEY_E)) {
			m_CameraRotate -= CameraMoveRotate * timeStep;
		}
		
		Dimon::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Dimon::RendererCommand::Clear();

		m_Camera.SetPosition(CameraProsition);
		m_Camera.SetRotation(m_CameraRotate);

		Dimon::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));


		std::dynamic_pointer_cast<Dimon::OpenGLShader>(m_Shader2)->Bind();
		std::dynamic_pointer_cast<Dimon::OpenGLShader>(m_Shader2)->SetUniformFloat3("u_Color", m_SquereColor);

		for (int x = 0; x < 20; x++)
		{
			for (int y = 0; y < 20; y++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);

				glm::mat4 trnasform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Dimon::Renderer::Submit(m_SquereVertexArray, m_Shader2, trnasform);
			}
		}
		m_Texture->Bind();
		auto textShader = m_ShaderLibrary.Get("TextShaderImage");
		Dimon::Renderer::Submit(m_SquereVertexArray, textShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_ChernoTexture->Bind();
		Dimon::Renderer::Submit(m_SquereVertexArray, textShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		//Triangle
		//Dimon::Renderer::Submit(m_vertexArray, m_Shader);

		Dimon::Renderer::EndScene();
	}
	void OnEvent(Dimon::Event& event) override {

		if (event.GetEventType() == Dimon::EventType::KeyPressed) {
			Dimon::KeyPressedEvent& e = (Dimon::KeyPressedEvent&)event;
			DM_CLIENT_INFO("{0}", (char)e.GetKeyCode());
		}
		//DM_CLIENT_TRACE("{0}", event);

		Dimon::EventDispatcher dispacher(event);
		dispacher.Dispatch<Dimon::KeyPressedEvent>(DM_BIND_EVENT_FN(ExampleLeyer::OnKeyPressed));
	}
	bool OnKeyPressed(Dimon::KeyPressedEvent& e) {
		return false;
	}
	virtual void OnImGuiRender() override {
		ImGui::Begin("Test");
		ImGui::ColorEdit3("For Example", glm::value_ptr(m_SquereColor));
		ImGui::End();
	}
private:
	Dimon::ShaderLibrery m_ShaderLibrary;
	Dimon::Ref<Dimon::Shader> m_Shader;
	Dimon::Ref<Dimon::Shader> m_Shader2;

	Dimon::Ref<Dimon::VertexArray> m_vertexArray;
	Dimon::Ref<Dimon::VertexArray> m_SquereVertexArray;

	Dimon::Ref<Dimon::Texture2D> m_Texture,m_ChernoTexture;


	Dimon::OrthographicCamera m_Camera;
	glm::vec3 CameraProsition;
	float CameraMoveSpeed = 2.0f;

	glm::vec3 m_SquereColor = { 0.2f, 0.3f, 0.8f };


	float m_CameraRotate = 0.0f;
	float CameraMoveRotate = 30.0f;
};

class DimonGame : public Dimon::Application
{
public:
	DimonGame() { 
		PushLayer(new  ExampleLeyer()); 
	}
	~DimonGame() {};
};

Dimon::Application* Dimon::CreateApplication() {
	return new DimonGame();
}