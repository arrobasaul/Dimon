#include "dmpch.h"
#include "Renderer2D.h"
#include "RendererCommand.h"

#include <glm/gtc/type_ptr.hpp>

namespace Dimon {
	struct Renderer2DStorage {
		Ref<VertexArray> QuadVA;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
	};
	static Renderer2DStorage* s_Renderer2DStorage;
	void Renderer2D::Init()
	{
		s_Renderer2DStorage = new Renderer2DStorage();
		s_Renderer2DStorage->QuadVA = VertexArray::Create();
		float vertices2[5 * 4] = {
		   -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		   -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Ref<VertexBuffer> squereVB;
		squereVB.reset(VertexBuffer::Create(vertices2, sizeof(vertices2)));
		BufferLayout layout2 = {
			{ShaderDataType::Float3,"a_Position"},
			{ShaderDataType::Float2,"a_TextCoord"}
		};
		squereVB->SetLayout(layout2);
		s_Renderer2DStorage->QuadVA->AddVertexBuffer(squereVB);

		unsigned int indices2[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squereIB;
		squereIB.reset(IndexBuffer::Create(indices2, sizeof(indices2) / sizeof(uint32_t)));
		s_Renderer2DStorage->QuadVA->AddIndexBuffer(squereIB);
		
		s_Renderer2DStorage->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Renderer2DStorage->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		s_Renderer2DStorage->TextureShader = Shader::Create("TextShader","Resources/Shaders/TextShader.vert", "Resources/Shaders/TextShader.frag");
		s_Renderer2DStorage->TextureShader->Bind();
		s_Renderer2DStorage->TextureShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Showtow()
	{
		delete s_Renderer2DStorage;
	}

	void Renderer2D::BeginScene(OrthographicCamera camera)
	{
		s_Renderer2DStorage->TextureShader->Bind();
		s_Renderer2DStorage->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y ,0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		s_Renderer2DStorage->TextureShader->SetFloat4("u_Color", color);
		s_Renderer2DStorage->WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Renderer2DStorage->TextureShader->SetMat4("u_Transform", transform);

		s_Renderer2DStorage->QuadVA->Bind();
		RendererCommand::DrawIndexed(s_Renderer2DStorage->QuadVA);
	}
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tiling)
	{
		DrawQuad({ position.x, position.y ,0.0f }, size, texture, tiling);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tiling)
	{
		s_Renderer2DStorage->TextureShader->SetFloat4("u_Color", glm::vec4(1.0f));// glm::vec4(1.0f));
		//s_Renderer2DStorage->WhiteTexture->Bind();
		s_Renderer2DStorage->TextureShader->SetFloat("u_TilingFactor", tiling);
		texture->Bind();
		
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Renderer2DStorage->TextureShader->SetMat4("u_Transform", transform);


		s_Renderer2DStorage->QuadVA->Bind();
		RendererCommand::DrawIndexed(s_Renderer2DStorage->QuadVA);
	}
	void Renderer2D::DrawRotateQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawRotateQuad({ position.x, position.y ,0.0f }, size, rotation, color);
	}
	void Renderer2D::DrawRotateQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		//DM_PROFILE_FUNTION();
		s_Renderer2DStorage->TextureShader->SetFloat4("u_Color", color);
		s_Renderer2DStorage->TextureShader->SetFloat("u_TilingFactor", 1.0f);

		s_Renderer2DStorage->WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), rotation,  { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Renderer2DStorage->TextureShader->SetMat4("u_Transform", transform);

		s_Renderer2DStorage->QuadVA->Bind();
		RendererCommand::DrawIndexed(s_Renderer2DStorage->QuadVA);
	}
	void Renderer2D::DrawRotateQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tiling)
	{
		DrawRotateQuad({ position.x, position.y ,0.0f }, size, rotation, texture, tiling);
	}
	void Renderer2D::DrawRotateQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tiling)
	{
		s_Renderer2DStorage->TextureShader->SetFloat4("u_Color", glm::vec4(1.0f));// glm::vec4(1.0f));
		//s_Renderer2DStorage->WhiteTexture->Bind();
		s_Renderer2DStorage->TextureShader->SetFloat("u_TilingFactor", tiling);

		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Renderer2DStorage->TextureShader->SetMat4("u_Transform", transform);


		s_Renderer2DStorage->QuadVA->Bind();
		RendererCommand::DrawIndexed(s_Renderer2DStorage->QuadVA);
	}
}