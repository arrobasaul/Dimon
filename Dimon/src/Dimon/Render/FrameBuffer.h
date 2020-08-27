#pragma once
#include "Dimon/Core/Core.h"

namespace Dimon{
	struct FramebufferSpesification {
		uint32_t Width, Height;
		uint32_t Sample;
		bool SwapChainTarget = false;
	};
	class FrameBuffer {
	public:
		virtual ~FrameBuffer() = default;
		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual void Resize(uint32_t width, uint32_t heigth) = 0;

		virtual uint32_t GetColorAttachmentRendererID() const =0;
		virtual const FramebufferSpesification& GetSpesification() const = 0;
		static Ref<FrameBuffer> Create(const FramebufferSpesification& spec);
	};

}