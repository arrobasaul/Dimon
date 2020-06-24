#pragma once
#include "Dimon/Render/GraphicsContext.h"
struct GLFWwindow;
namespace Dimon {
	class OpenGLContext :public GraphicsContext {
	public:
		OpenGLContext(GLFWwindow* window);
		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_Window;
	};
}