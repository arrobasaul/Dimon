#include "dmpch.h"
#include "Dimon/Core/CoreInput.h"
#include "Dimon/Core/Application.h"
#include <GLFW/glfw3.h>
namespace Dimon {
	bool CoreInput::IsKeyPressed(int key)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, key);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool CoreInput::IsMouseButtonPressed(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> CoreInput::GetMousePosition()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double x, y;
		glfwGetCursorPos(window,&x,&y);
		return {(float)x, (float)y};
	}

	float CoreInput::GetMouseX()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto[x,y] = GetMousePosition();
		return x;
	}

	float CoreInput::GetMouseY()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto [x, y] = GetMousePosition();
		return y;
	}
}

