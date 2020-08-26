#include "dmpch.h"
#include "SubTexture2D.h"
namespace Dimon {
	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2 min, const glm::vec2 max)
		:m_Texture(texture)
	{
		m_TexCoord[0] = { min.x ,min.y };
		m_TexCoord[1] = { max.x ,min.y };
		m_TexCoord[2] = { max.x ,max.y };
		m_TexCoord[3] = { min.x ,max.y };
	}
	Ref<SubTexture2D> SubTexture2D::CreateFromCoord(const Ref<Texture2D>& texture, glm::vec2 coords, const glm::vec2 cellSize, const glm::vec2 spriteSize)
	{
		glm::vec2 min = glm::vec2({ (coords.x * cellSize.x) / texture->GetWith(), (coords.y * cellSize.y) / texture->GetHeight() });
		glm::vec2 max =	glm::vec2({ ((coords.x + spriteSize.x) * cellSize.x) / texture->GetWith(), ((coords.y + spriteSize.y) * cellSize.y) / texture->GetHeight() });
		return  CreateRef<SubTexture2D>(texture, min, max);
	}
}