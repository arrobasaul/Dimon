#pragma once
#include <cstdint>
#include <string>
#include "Dimon/Core/Core.h"
namespace Dimon {
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWith() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetData(void* data, uint32_t size) = 0;
		virtual void Bind(uint32_t unit = 0) const = 0;

	private:

	};
	class Texture2D : public Texture {
	public:
		static Ref<Texture2D> Create(uint32_t width, uint32_t heigth);
		static Ref<Texture2D> Create(const std::string& path);
	};
}