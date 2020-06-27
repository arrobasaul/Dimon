#include "dmpch.h"
#include "RendererCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"
namespace Dimon {
	RendererAPI* RendererCommand::s_RendererAPI = new OpenGLRendererAPI;
}