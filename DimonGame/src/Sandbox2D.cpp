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
		Dimon::Renderer2D::DrawRotateQuad(glm::vec2({ -1.0f,1.0f }), glm::vec2({ 0.8f,0.8f }), glm::radians(contador), m_SquereColor);
		Dimon::Renderer2D::DrawQuad(glm::vec2({ -1.0f,0.0f }), glm::vec2({ 0.8f,0.8f }), m_SquereColor);
		Dimon::Renderer2D::DrawQuad(glm::vec2({ 0.0f,-0.5f }), glm::vec2({ 0.5f,0.75f }), m_SquereColor);
		Dimon::Renderer2D::DrawRotateQuad(glm::vec3({ 0.2f, 0.5f,-0.0f }), glm::vec2({ 10.0f,10.0f }), glm::radians(contador), m_DimonTexture);
		Dimon::Renderer2D::EndScene();
	}
	contador+=0.5f;
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Setting");
	ImGui::ColorEdit4("Color", glm::value_ptr(m_SquereColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Dimon::Event& event)
{
	m_CameraController.OnEvent(event);
}
