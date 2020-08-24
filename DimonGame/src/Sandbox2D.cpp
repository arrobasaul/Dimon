#include "Sandbox2D.h"
#include "ImGui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"
#include "Dimon/Debug/Intrumentor.h"

Sandbox2D::Sandbox2D()
	: Layer("Minecraf"), m_CameraController(1920.0f / 1440.0f)
{
}
void Sandbox2D::OnAttach()
{
	//auto textureShader = m_ShaderLibrary.Load("TextShaderImage", "Resources/Shaders/TextShader.vert", "Resources/Shaders/TextShader.frag");
	m_DimonTexture = Dimon::Texture2D::Create("Resources/Texture/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Dimon::TimeStep timeStep)
{
	DM_PROFILE_FUNCTION();
	{
		DM_PROFILE_SCOPE("m_CameraController.OnUpdate");
		m_CameraController.OnUpdate(timeStep);
	}
	Dimon::Renderer2D::ResetStat();
	{
		DM_PROFILE_SCOPE("Sandbox2D::Render");
		Dimon::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Dimon::RendererCommand::Clear();
	}
	if (contador == 90.0f)
		contador = -90.0f;
	{
		DM_PROFILE_SCOPE("Sandbox2D::Draw");
		Dimon::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Dimon::Renderer2D::DrawRotateQuad(glm::vec2({ 1.0f,0.0f }), glm::vec2({ 0.8f,0.8f }), contador, m_SquereColor);

		Dimon::Renderer2D::DrawQuad(glm::vec2({ -1.0f,0.0f }), glm::vec2({ 0.8f,0.8f }), m_SquereColor);
		Dimon::Renderer2D::DrawQuad(glm::vec2({ 0.5f,-0.5f }), glm::vec2({ 0.5f,0.75f }), m_SquereColor);
		Dimon::Renderer2D::DrawQuad(glm::vec3({ -5.0f, -5.0f,-0.1f }), glm::vec2({ 10.0f,10.0f }), m_DimonTexture, 10.0f);
		//Dimon::Renderer2D::DrawQuad(glm::vec2({ 0.0f,-0.5f }), glm::vec2({ 0.5f,0.75f }), { 0.1f, 1.0f, 0.1f, 1.0f });
		Dimon::Renderer2D::DrawRotateQuad(glm::vec3({ -2.0f, 0.0f,0.0f }), glm::vec2({ 1.0f,1.0f }), contador, m_DimonTexture, 20.0f);
		Dimon::Renderer2D::EndScene();

		Dimon::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -0.5f; y < 5.0f; y += 0.5f)
		{
			for (float x = -0.5f; x < 5.0f; x += 0.5f)
			{
				Dimon::Renderer2D::DrawRotateQuad(glm::vec2({ x,y }), glm::vec2({ 0.45f,0.45f }), 45, m_SquereColor);
				//Dimon::Renderer2D::DrawQuad(glm::vec2({ x,y }), glm::vec2({ 0.45f,0.45f }), { 1.0f, 0.1f, 0.1f, 1.0f });
			}
		}

		Dimon::Renderer2D::EndScene();

	}
	contador+=0.5f;
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Setting");
	auto stats = Dimon::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quad Counts: %d", stats.QuadCount);
	ImGui::Text("Index Counts: %d", stats.GetTotalIndexCount());
	ImGui::Text("Vertex Counts: %d", stats.GetTotalVertexCount());

	ImGui::ColorEdit4("Color", glm::value_ptr(m_SquereColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Dimon::Event& event)
{
	m_CameraController.OnEvent(event);
}
