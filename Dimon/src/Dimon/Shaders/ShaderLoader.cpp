#include "dmpch.h"
#include "ShaderLoader.h"
#include "Dimon/Util/FileUtil.h"
#include "Dimon/Log.h"
namespace Dimon {
    GLuint compileShader(const GLchar* source, GLenum shaderType)
    {
        auto shaderID = glCreateShader(shaderType);

        glShaderSource(shaderID, 1, &source, 0);
        glCompileShader(shaderID);

        GLint isSuccess = 0;
        GLchar infoLog[512];

        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isSuccess);
        if (!isSuccess) {
            glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
            DM_CORE_ERROR("Unable to load a shader: {0}", infoLog);
            glDeleteShader(shaderID);
            //throw std::runtime_error("Unable to load a shader: " + std::string(infoLog));
        }

        return shaderID;
    }

    GLuint linkProgram(GLuint vertexShaderID, GLuint fragmentShaderID)
    {
        auto program = glCreateProgram();

        glAttachShader(program, vertexShaderID);
        glAttachShader(program, fragmentShaderID);

        glLinkProgram(program);
        GLint isSuccess = 0;
        GLchar infoLog[512];
        glGetShaderiv(program, GL_LINK_STATUS, &isSuccess);
        if (!isSuccess) {
            glGetProgramInfoLog(program, 512, nullptr, infoLog);
            DM_CORE_ERROR("Unable to load a Program: {0}", infoLog);
            //throw std::runtime_error("Unable to load a shader: " + std::string(infoLog));
            glDeleteProgram(program);
            glDeleteShader(vertexShaderID);
            glDeleteShader(fragmentShaderID);
        }
        return program;
    }
    GLuint Dimon::loadShaders(const std::string& vertexShader, const std::string& fragmentShader)
    {
        auto vertexSource = getFileContents("src/Resources/Shaders/" + vertexShader + ".vert");
        auto fragmentSource = getFileContents("src/Resources/Shaders/" + fragmentShader + ".frag");

        auto vertexShaderID = compileShader(vertexSource.c_str(), GL_VERTEX_SHADER);
        auto fragmentShaderID = compileShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER);

        auto shaderID = linkProgram(vertexShaderID, fragmentShaderID);

        glDetachShader(shaderID,vertexShaderID);
        glDetachShader(shaderID,fragmentShaderID);

        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);

        return shaderID;
    }
} // namespace

