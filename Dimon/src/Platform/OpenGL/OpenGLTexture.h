#pragma once
#include "Texture.h"
namespace Dimon {
	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(const std::string& path);
		~OpenGLTexture2D();
		virtual uint32_t GetWith() const override { return m_Width; };
		virtual uint32_t GetHeight() const override { return m_Height; };

		virtual void Bind(uint32_t init = 0) const override;
	private:
		std::string m_path;
		uint32_t m_Width;
		uint32_t m_Height;
		uint32_t m_RendererID;
	};
}