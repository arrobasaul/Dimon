#include "dmpch.h"
#include "OpenGLVertexArray.h"

#include "glad/glad.h"

namespace Dimon {
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type)
		{
		case Dimon::ShaderDataType::None:		return GL_FLOAT;
		case Dimon::ShaderDataType::Float:		return GL_FLOAT;
		case Dimon::ShaderDataType::Float2:		return GL_FLOAT;
		case Dimon::ShaderDataType::Float3:		return GL_FLOAT;
		case Dimon::ShaderDataType::Float4:		return GL_FLOAT;
		case Dimon::ShaderDataType::Mat3:		return GL_FLOAT;
		case Dimon::ShaderDataType::Mat4:		return GL_FLOAT;
		case Dimon::ShaderDataType::Int:		return GL_INT;
		case Dimon::ShaderDataType::Int2:		return GL_INT;
		case Dimon::ShaderDataType::Int3:		return GL_INT;
		case Dimon::ShaderDataType::Int4:		return GL_INT;
		}
		DM_CORE_ASSERT(false, "unknown ShaderDataType");
		return 0;
	}
	OpenGLVertexArray::OpenGLVertexArray() {
		glCreateVertexArrays(1, &m_RenderID);
	}
	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RenderID);
	}
	void OpenGLVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}
	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		DM_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Bubberr has no Layout");

		glBindVertexArray(m_RenderID);
		vertexBuffer->Bind();
		uint16_t layoutcount = 0;
		for (const auto& element : vertexBuffer->GetLayout()) {
			glEnableVertexAttribArray(layoutcount);
			glVertexAttribPointer(layoutcount,
				element.GetComponetCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				vertexBuffer->GetLayout().GetStride(),
				(const void*)element.Offset);
			layoutcount++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}
	void OpenGLVertexArray::AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RenderID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}
}

