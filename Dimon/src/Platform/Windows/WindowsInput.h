#include "dmpch.h"
#include "Dimon/CoreInput.h"
namespace Dimon {
	class WindowsInput : public CoreInput {
	protected:
		virtual bool IsKeyPressedImpl(int key) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}