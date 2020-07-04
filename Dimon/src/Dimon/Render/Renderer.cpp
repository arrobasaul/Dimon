#include "dmpch.h"
#include "Renderer.h"
#include "RendererCommand.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Dimon {
	Renderer::DataScene* Renderer::m_DataScene = new Renderer::DataScene;
	void Renderer::Init()
	{
		RendererCommand::Init();
	}
	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_DataScene->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(const Ref<VertexArray>& vertexArray,const Ref<Shader>& shader, glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniformMat4("u_ViewProjection", m_DataScene->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		RendererCommand::DrawIndexed(vertexArray);
	}
}