#include "dmpch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
namespace Dimon {
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		DM_CORE_ASSERT(false, "RendererAPI::None no supported"); return nullptr;
			case RendererAPI::API::OpenGL:		return new OpenGLVertexArray();
		default:
			break;
		}
		DM_CORE_ASSERT(false, "UnKnown");
		return nullptr;
	}
}