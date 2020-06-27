#include "dmpch.h"
#include "Buffer.h"
#include "Dimon/Render/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include <Dimon\Core.h>
namespace Dimon {
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:			DM_CORE_ASSERT(false, "RendererAPI::None no supported"); return nullptr;
		case RendererAPI::API::OpenGL:		return new OpenGLVertexBuffer(vertices, size);
		default:
			break;
		}
		DM_CORE_ASSERT(false, "UnKnown");
		return nullptr;
	}
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:			DM_CORE_ASSERT(false, "RendererAPI::None no supported"); return nullptr;
		case RendererAPI::API::OpenGL:		return new OpenGLIndexBuffer(indices, size);
		default:
			break;
		}
		DM_CORE_ASSERT(false, "UnKnown");
		return nullptr;
	}
}
