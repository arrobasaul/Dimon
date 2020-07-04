#pragma once
#include "Dimon/Render/VertexArray.h"
namespace Dimon {
	class OpenGLVertexArray : public VertexArray
	{
	public:
		virtual ~OpenGLVertexArray();
		OpenGLVertexArray();
		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void AddIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		virtual const Ref<IndexBuffer>& GetIndexBuffers() const { return m_IndexBuffer;  }

		static VertexArray* Create(float* vertices, uint32_t size);
	private:
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
		uint32_t m_RenderID;
	};
}