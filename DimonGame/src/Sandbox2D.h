#pragma once
#include <Dimon.h>

class Sandbox2D : public Dimon::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Dimon::TimeStep timeStep) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Dimon::Event& event) override;
private:
	Dimon::Ref<Dimon::Shader> m_FlatColorShader;
	Dimon::Ref<Dimon::VertexArray> m_VertexArray;

	Dimon::OrthographicCameraController m_CameraController;

	Dimon::Ref<Dimon::Texture2D> m_DimonTexture;
	glm::vec4 m_SquereColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	float contador = -90.0f;
};
