#pragma once

#include "glad/glad.h"

namespace Dimon {
	GLuint loadShaders(const std::string& vertexShader,
		const std::string& fragmentShader);
}