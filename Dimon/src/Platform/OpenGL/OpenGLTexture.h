#pragma once
#include "Dimon/Render/Texture.h"
#include "glad/glad.h"
namespace Dimon {
	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(uint32_t width, uint32_t heigth);
		OpenGLTexture2D(const std::string& path);
		~OpenGLTexture2D();
		virtual uint32_t GetWith() const override { return m_Width; };
		virtual uint32_t GetHeight() const override { return m_Height; };
		virtual void SetData(void* data, uint32_t size) override;


		virtual void Bind(uint32_t unit = 0) const override;
		virtual bool operator==(const Texture& other) const override { 
			return m_RendererID == ((OpenGLTexture2D&)other).m_RendererID;
		}  
	private:
		std::string m_path;
		uint32_t m_Width;
		uint32_t m_Height;
		uint32_t m_RendererID;
		GLenum m_DataFormat, m_InternalFormat;
	};
}