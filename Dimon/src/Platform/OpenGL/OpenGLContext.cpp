#include "dmpch.h"
#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <Dimon/Core.h>
#include "Dimon/Log.h"
namespace Dimon {
	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_Window(window)
	{
		DM_CORE_ASSERT(window,"window is null")
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		DM_CORE_ASSERT(status, "Error to inicialize GLAD");
		DM_CORE_INFO("OpenGL Info: GL_VENDOR: {0}- GL_RENDERER: {1} - GL_VERSION: {2}", glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}
}