#include "dmpch.h"
#include "WindowsInput.h"
#include "Dimon/Application.h"
#include <GLFW/glfw3.h>
namespace Dimon {
	CoreInput* CoreInput::s_Instance = new WindowsInput();

	bool Dimon::WindowsInput::IsKeyPressedImpl(int key)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, key);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Dimon::WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}

	std::pair<float, float> Dimon::WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double x, y;
		glfwGetCursorPos(window,&x,&y);
		return {(float)x, (float)y};
	}

	float Dimon::WindowsInput::GetMouseXImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto[x,y] = GetMousePositionImpl();
		return x;
	}

	float Dimon::WindowsInput::GetMouseYImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto [x, y] = GetMousePositionImpl();
		return y;
	}
}

