#include "dmpch.h"
#include "FrameBuffer.h"
#include "Dimon/Core/Core.h"
#include "Dimon/Render/Renderer.h"
#include "Platform/OpenGL/OpenGLFrameBuffer.h"


namespace Dimon {
	Ref<FrameBuffer> FrameBuffer::Create(const FramebufferSpesification& spec)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:			DM_CORE_ASSERT(false, "RendererAPI::None no supported"); return nullptr;
			case RendererAPI::API::OpenGL:		return CreateRef<OpenGLFrameBuffer>(spec);
			default:
				break;
		}
		DM_CORE_ASSERT(false, "UnKnown");
		return nullptr;
	}
}