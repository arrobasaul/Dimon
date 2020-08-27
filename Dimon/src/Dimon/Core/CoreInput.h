#pragma once

#include "Dimon/Core/Core.h"
#include <utility>

namespace Dimon {
	class DIMON_API CoreInput
	{
	protected:
	public:
		static bool IsKeyPressed(int key);

		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}