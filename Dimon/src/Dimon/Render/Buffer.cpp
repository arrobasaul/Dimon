#include "dmpch.h"
#include "Buffer.h"
#include "Dimon/Render/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Dimon/Core/Core.h"
namespace Dimon {
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:			DM_CORE_ASSERT(false, "RendererAPI::None no supported"); return nullptr;
			case RendererAPI::API::OpenGL:		return std::make_shared <OpenGLVertexBuffer>(size);
		default:
			break;
		}
		DM_CORE_ASSERT(false, "UnKnown");
		return nullptr;
	}
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:			DM_CORE_ASSERT(false, "RendererAPI::None no supported"); return nullptr;
			case RendererAPI::API::OpenGL:		return std::make_shared <OpenGLVertexBuffer>(vertices, size);
		default:
			break;
		}
		DM_CORE_ASSERT(false, "UnKnown");
		return nullptr;
	}
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:			DM_CORE_ASSERT(false, "RendererAPI::None no supported"); return nullptr;
			case RendererAPI::API::OpenGL:		return std::make_shared <OpenGLIndexBuffer>(indices, count);
		default:
			break;
		}
		DM_CORE_ASSERT(false, "UnKnown");
		return nullptr;
	}
}
