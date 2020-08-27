#pragma once
#include "Dimon/Render/FrameBuffer.h"
namespace Dimon {
	class OpenGLFrameBuffer : public FrameBuffer{
	public:
		OpenGLFrameBuffer(const FramebufferSpesification& spec);
		virtual ~OpenGLFrameBuffer();
		void Recreate();

		virtual void Bind() override;
		virtual void UnBind() override;

		virtual void Resize(uint32_t width, uint32_t heigth) override;
		virtual const FramebufferSpesification& GetSpesification() const override{
			return m_Specification;
		}
		virtual uint32_t GetColorAttachmentRendererID() const override { 
			return m_ColorAttachment; 
		}
	private:
		uint32_t m_RendererID;
		uint32_t m_ColorAttachment, m_DepthAttachment;
		FramebufferSpesification m_Specification;
	};
}