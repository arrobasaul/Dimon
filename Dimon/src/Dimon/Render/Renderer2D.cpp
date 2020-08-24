#include "dmpch.h"
#include "Renderer2D.h"
#include "RendererCommand.h"

#include <glm/gtc/type_ptr.hpp>

namespace Dimon {
	struct QuadVertex {
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
		float TilingFactor;
	};

	struct Renderer2DStorage {
		static const uint32_t MaxQuads = 20000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32;

		Ref<VertexArray> QuadVA;
		Ref<VertexBuffer> QuadVB;

		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		std::array<Ref<Texture2D>, MaxTextureSlots> TexturesSlots;
		const std::array<glm::vec2, 4> s_TexCoord { 
			glm::vec2({ 0.0f, 0.0f }),
			glm::vec2({ 1.0f, 0.0f }),
			glm::vec2({ 1.0f, 1.0f }), 
			glm::vec2({ 0.0f, 1.0f }) 
		};
		uint32_t TextureSlotIndex = 1;
		glm::vec4 QuadVertexPosition[4];

		Renderer2D::Statistic Stats;
	};
	static Renderer2DStorage s_Renderer2DStorage;

	void Renderer2D::Init()
	{
		s_Renderer2DStorage.QuadVA = VertexArray::Create();

		s_Renderer2DStorage.QuadVB =VertexBuffer::Create(s_Renderer2DStorage.MaxVertices * sizeof(QuadVertex));
		BufferLayout layout2 = {
			{ShaderDataType::Float3,"a_Position"},
			{ShaderDataType::Float4,"a_Color"},
			{ShaderDataType::Float2,"a_TexCoord"},
			{ShaderDataType::Float,"a_TexIndex"},
			{ShaderDataType::Float,"a_TilingFactor"}
		};
		s_Renderer2DStorage.QuadVB->SetLayout(layout2);
		s_Renderer2DStorage.QuadVA->AddVertexBuffer(s_Renderer2DStorage.QuadVB);

		s_Renderer2DStorage.QuadVertexBufferBase = new QuadVertex[s_Renderer2DStorage.MaxVertices];

		uint32_t* quadIndices = new uint32_t[s_Renderer2DStorage.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Renderer2DStorage.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;
			
			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Renderer2DStorage.MaxIndices );
		s_Renderer2DStorage.QuadVA->AddIndexBuffer(quadIB);
		delete[] quadIndices;

		s_Renderer2DStorage.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Renderer2DStorage.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		int32_t samplers[s_Renderer2DStorage.MaxTextureSlots];
		for (uint32_t i = 0; i < s_Renderer2DStorage.MaxTextureSlots; i++)
			samplers[i] = i;

		s_Renderer2DStorage.TextureShader = Shader::Create("TextShader", "Resources/Shaders/TextShader.vert", "Resources/Shaders/TextShader.frag");
		s_Renderer2DStorage.TextureShader->Bind();
		s_Renderer2DStorage.TextureShader->SetIntArray("u_Textures", samplers, s_Renderer2DStorage.MaxTextureSlots);

		s_Renderer2DStorage.TexturesSlots[0] = s_Renderer2DStorage.WhiteTexture;

		s_Renderer2DStorage.QuadVertexPosition[0] = {-0.5f, -0.5f, 0.0f, 1.0f};
		s_Renderer2DStorage.QuadVertexPosition[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_Renderer2DStorage.QuadVertexPosition[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		s_Renderer2DStorage.QuadVertexPosition[3] = {-0.5f,  0.5f, 0.0f, 1.0f };
	}

	void Renderer2D::Showtow()
	{
		
	}

	void Renderer2D::BeginScene(OrthographicCamera camera)
	{
		s_Renderer2DStorage.TextureShader->Bind();
		s_Renderer2DStorage.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		s_Renderer2DStorage.QuadIndexCount = 0;

		s_Renderer2DStorage.QuadVertexBufferPtr = s_Renderer2DStorage.QuadVertexBufferBase;
		s_Renderer2DStorage.TextureSlotIndex = 1;
	}

	void Renderer2D::EndScene()
	{
		uint32_t datasize = (uint8_t*)s_Renderer2DStorage.QuadVertexBufferPtr - (uint8_t*)s_Renderer2DStorage.QuadVertexBufferBase;
		s_Renderer2DStorage.QuadVB->SetData(s_Renderer2DStorage.QuadVertexBufferBase, datasize);
		Flush();
	}

	void Renderer2D::Flush()
	{
		for (uint32_t i = 0; i < s_Renderer2DStorage.TextureSlotIndex; i++) {
			s_Renderer2DStorage.TexturesSlots[i]->Bind(i);
		}
		RendererCommand::DrawIndexed(s_Renderer2DStorage.QuadVA, s_Renderer2DStorage.QuadIndexCount);
		s_Renderer2DStorage.Stats.DrawCalls++;
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y ,0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		if (s_Renderer2DStorage.QuadIndexCount >= s_Renderer2DStorage.MaxIndices)
			StartNewBatch();

		const float texIndex = 0.0f;
		const float tilingFactor = 10.0f;

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) 
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		
		for (int i = 0; i < 4; i++)
		{
			s_Renderer2DStorage.QuadVertexBufferPtr->Position = transform * s_Renderer2DStorage.QuadVertexPosition[i];
			s_Renderer2DStorage.QuadVertexBufferPtr->Color = color;
			s_Renderer2DStorage.QuadVertexBufferPtr->TexCoord = s_Renderer2DStorage.s_TexCoord[i];
			s_Renderer2DStorage.QuadVertexBufferPtr->TexIndex = texIndex;
			s_Renderer2DStorage.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			s_Renderer2DStorage.QuadVertexBufferPtr++;
		}
		s_Renderer2DStorage.QuadIndexCount += 6;
		s_Renderer2DStorage.Stats.QuadCount++;
	}
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tiling, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y ,0.0f }, size, texture, tiling, color);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tiling, const glm::vec4& color)
	{
		if (s_Renderer2DStorage.QuadIndexCount >= s_Renderer2DStorage.MaxIndices)
			StartNewBatch();
		constexpr glm::vec4 colors = { 1.0f,1.0f,1.0f,1.0f }; 

		float textureIndex = 0.0f;

		for (uint32_t i = 0; i < s_Renderer2DStorage.TextureSlotIndex; i++) {
			if (*s_Renderer2DStorage.TexturesSlots[i].get() == *texture.get()) {
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f) {
			textureIndex = (float)s_Renderer2DStorage.TextureSlotIndex;
			s_Renderer2DStorage.TexturesSlots[s_Renderer2DStorage.TextureSlotIndex] = texture;
			s_Renderer2DStorage.TextureSlotIndex++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });


		for (int i = 0; i < 4; i++)
		{
			s_Renderer2DStorage.QuadVertexBufferPtr->Position = transform * s_Renderer2DStorage.QuadVertexPosition[i];
			s_Renderer2DStorage.QuadVertexBufferPtr->Color = color;
			s_Renderer2DStorage.QuadVertexBufferPtr->TexCoord = s_Renderer2DStorage.s_TexCoord[i];
			s_Renderer2DStorage.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Renderer2DStorage.QuadVertexBufferPtr->TilingFactor = tiling;
			s_Renderer2DStorage.QuadVertexBufferPtr++;
		}
		s_Renderer2DStorage.QuadIndexCount += 6;
		s_Renderer2DStorage.Stats.QuadCount++;
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y ,0.0f }, size, rotation, color);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		s_Renderer2DStorage.TextureShader->SetFloat4("u_Color", color);
		s_Renderer2DStorage.WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Renderer2DStorage.TextureShader->SetMat4("u_Transform", transform);
		s_Renderer2DStorage.QuadVA->Bind();
		RendererCommand::DrawIndexed(s_Renderer2DStorage.QuadVA);
	}

	void Renderer2D::DrawRotateQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawRotateQuad({ position.x, position.y ,0.0f }, size, rotation, color);
	}
	void Renderer2D::DrawRotateQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		//DM_PROFILE_FUNTION();
		if (s_Renderer2DStorage.QuadIndexCount >= s_Renderer2DStorage.MaxIndices)
			StartNewBatch();
		const float texIndex = 0.0f;
		const float tilingFactor = 10.0f;
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		for (int i = 0; i < 4; i++)
		{
			s_Renderer2DStorage.QuadVertexBufferPtr->Position = transform * s_Renderer2DStorage.QuadVertexPosition[i];
			s_Renderer2DStorage.QuadVertexBufferPtr->Color = color;
			s_Renderer2DStorage.QuadVertexBufferPtr->TexCoord = s_Renderer2DStorage.s_TexCoord[i];
			s_Renderer2DStorage.QuadVertexBufferPtr->TexIndex = texIndex;
			s_Renderer2DStorage.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			s_Renderer2DStorage.QuadVertexBufferPtr++;
		}
		s_Renderer2DStorage.QuadIndexCount += 6;
		s_Renderer2DStorage.Stats.QuadCount++;
	}
	void Renderer2D::DrawRotateQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tiling , const glm::vec4& color)
	{
		DrawRotateQuad({ position.x, position.y ,0.0f }, size, rotation, texture, tiling, color);
	}
	void Renderer2D::DrawRotateQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tiling , const glm::vec4& color)
	{
		if (s_Renderer2DStorage.QuadIndexCount >= s_Renderer2DStorage.MaxIndices)
			StartNewBatch();
		constexpr glm::vec4 colors = { 1.0f,1.0f,1.0f,1.0f };

		float textureIndex = 0.0f;

		for (uint32_t i = 0; i < s_Renderer2DStorage.TextureSlotIndex; i++) {
			if (*s_Renderer2DStorage.TexturesSlots[i].get() == *texture.get()) {
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f) {
			textureIndex = (float)s_Renderer2DStorage.TextureSlotIndex;
			s_Renderer2DStorage.TexturesSlots[s_Renderer2DStorage.TextureSlotIndex] = texture;
			s_Renderer2DStorage.TextureSlotIndex++;
		}
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		for (int i = 0; i < 4; i++)
		{
			s_Renderer2DStorage.QuadVertexBufferPtr->Position = transform * s_Renderer2DStorage.QuadVertexPosition[i];
			s_Renderer2DStorage.QuadVertexBufferPtr->Color = color;
			s_Renderer2DStorage.QuadVertexBufferPtr->TexCoord = s_Renderer2DStorage.s_TexCoord[i];
			s_Renderer2DStorage.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Renderer2DStorage.QuadVertexBufferPtr->TilingFactor = tiling;
			s_Renderer2DStorage.QuadVertexBufferPtr++;
		}
		s_Renderer2DStorage.QuadIndexCount += 6;
		s_Renderer2DStorage.Stats.QuadCount++;
#if 0
		s_Renderer2DStorage.TextureShader->SetFloat4("u_Color", glm::vec4(1.0f));// glm::vec4(1.0f));
		//s_Renderer2DStorage.WhiteTexture->Bind();
		s_Renderer2DStorage.TextureShader->SetFloat("u_TilingFactor", tiling);

		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Renderer2DStorage.TextureShader->SetMat4("u_Transform", transform);


		s_Renderer2DStorage.QuadVA->Bind();
		RendererCommand::DrawIndexed(s_Renderer2DStorage.QuadVA);
#endif
	}
	void Renderer2D::ResetStat()
	{
		memset(&s_Renderer2DStorage.Stats, 0, sizeof(Renderer2D::Statistic));
	}
	Renderer2D::Statistic Renderer2D::GetStats()
	{
		return s_Renderer2DStorage.Stats;
	}
	void Renderer2D::StartNewBatch()
	{
		EndScene();
		s_Renderer2DStorage.QuadIndexCount = 0;

		s_Renderer2DStorage.QuadVertexBufferPtr = s_Renderer2DStorage.QuadVertexBufferBase;
		s_Renderer2DStorage.TextureSlotIndex = 1;
	}
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, rotation, texture, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec4& color)
	{
		const float texIndex = 0.0f;
		const float tilingFactor = 10.0f;

		if (s_Renderer2DStorage.QuadIndexCount >= s_Renderer2DStorage.MaxIndices)
			StartNewBatch();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) 
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) 
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		for (int i = 0; i < 4; i++)
		{
			s_Renderer2DStorage.QuadVertexBufferPtr->Position = transform * s_Renderer2DStorage.QuadVertexPosition[i];
			s_Renderer2DStorage.QuadVertexBufferPtr->Color = color;
			s_Renderer2DStorage.QuadVertexBufferPtr->TexCoord = s_Renderer2DStorage.s_TexCoord[i];
			s_Renderer2DStorage.QuadVertexBufferPtr->TexIndex = texIndex;
			s_Renderer2DStorage.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			s_Renderer2DStorage.QuadVertexBufferPtr++;
		}
		s_Renderer2DStorage.QuadIndexCount += 6;
		s_Renderer2DStorage.Stats.QuadCount++;
	}
}