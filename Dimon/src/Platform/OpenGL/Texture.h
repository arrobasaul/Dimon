#pragma once
#include <cstdint>
#include <string>
#include "Dimon/Core.h"
namespace Dimon {
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWith() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void Bind(uint32_t unit = 0) const = 0;

	private:

	};
	class Texture2D : public Texture {
	public:
		static Ref<Texture2D> Create(const std::string& path);
	};
}