#include "dmpch.h"
#include "Texture.h"
#include "Dimon/Render/Renderer.h"
#include "OpenGLTexture.h"
namespace Dimon {
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t heigth)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		DM_CORE_ASSERT(false, "RendererAPI::None no supported"); return nullptr;
		case RendererAPI::API::OpenGL:		return CreateRef<OpenGLTexture2D>(width, heigth);
		default:
			break;
		}
		DM_CORE_ASSERT(false, "UnKnown");
		return nullptr;
	}
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		DM_CORE_ASSERT(false, "RendererAPI::None no supported"); return nullptr;
		case RendererAPI::API::OpenGL:		return CreateRef<OpenGLTexture2D>(path);
		default:
			break;
		}
		DM_CORE_ASSERT(false, "UnKnown");
		return nullptr;
	}
}