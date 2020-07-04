#include "dmpch.h"
#include "OpenGLTexture.h"
#include "stb_image.h"
#include "glad/glad.h"
namespace Dimon {
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		:m_path(path)
	{
		int width, height, chanels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc*  data = stbi_load(path.c_str(), &width, &height, &chanels, 0);
		DM_CORE_ASSERT(data, "Faild to load image");
		m_Width = width;
		m_Height = height;

		GLenum dataFormat = 0, internalFormat = 0;
		if (chanels == 4) {
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (chanels == 3) {
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}
		DM_CORE_ASSERT(internalFormat & dataFormat, "Format no sopported")
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}
	void OpenGLTexture2D::Bind(uint32_t unit) const
	{
		glBindTextureUnit(unit, m_RendererID);
	}
	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}
}