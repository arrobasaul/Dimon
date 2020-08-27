#pragma once
#include "Dimon.h"
namespace Dimon {
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(TimeStep timeStep) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;
	private:
		OrthographicCameraController m_CameraController;

		Ref<VertexArray> m_VertexArray;
		Ref<Shader> m_FlatColorShader;
		Ref<FrameBuffer> m_FrameBuffer;

		Ref<Texture2D> m_DimonTexture;
		glm::vec2 m_ViePortSize = {0.0f,0.0f};
		glm::vec4 m_SquereColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	};

}