#include "dmpch.h"

#include "Shader.h"
#include "Dimon/Util/FileUtil.h"
#include "Dimon/Log.h"

#include <glad/glad.h>
namespace Dimon {
    uint32_t Shader::compileShader(const char* source, uint32_t shaderType)
    {
        auto shaderID = glCreateShader(shaderType);

        glShaderSource(shaderID, 1, &source, 0);
        glCompileShader(shaderID);

        GLint isSuccess = 0;
        GLchar infoLog[512];

        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isSuccess);
        if (!isSuccess) {//if (isSuccess==GL_FALSE) {
            glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);//glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
            DM_CORE_ERROR("Unable to load a shader: {0}", infoLog);
            glDeleteShader(shaderID);
            //throw std::runtime_error("Unable to load a shader: " + std::string(infoLog));
        }

        return shaderID;
    }

    uint32_t Shader::linkProgram(uint32_t vertexShaderID, uint32_t fragmentShaderID)
    {
        GLuint program = glCreateProgram();

        glAttachShader(program, vertexShaderID);
        glAttachShader(program, fragmentShaderID);

        glLinkProgram(program);
        GLint isSuccess = 0;
        
        glGetShaderiv(program, GL_LINK_STATUS, &isSuccess);
        if (isSuccess) {
            GLint max = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &max);
            GLchar infoLog(max);

            glGetProgramInfoLog(program, max, &max, &infoLog);
            DM_CORE_ERROR("Unable to load a Program: {0}", infoLog );
            //throw std::runtime_error("Unable to load a shader: " + std::string(infoLog));
            glDeleteProgram(program);
            glDeleteShader(vertexShaderID);
            glDeleteShader(fragmentShaderID);
        }
        return program;
    }
    void Shader::Bind() const
    {
        glUseProgram(m_RenderID);
    }
    void Shader::UnBind() const
    {
        glUseProgram(0);
    }
    uint32_t Shader::loadShaders(const std::string& vertexShader, const std::string& fragmentShader)
    {
        auto vertexSource = getFileContents("D:/Code/c++/OpenGLRoot/Dimon/DimonGame/Resources/Shaders/" + vertexShader + ".vert");
        auto fragmentSource = getFileContents("D:/Code/c++/OpenGLRoot/Dimon/DimonGame/Resources/Shaders/" + fragmentShader + ".frag");

        auto vertexShaderID = compileShader(vertexSource.c_str(), GL_VERTEX_SHADER);
        auto fragmentShaderID = compileShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER);

        m_RenderID = linkProgram(vertexShaderID, fragmentShaderID);

        glDetachShader(m_RenderID,vertexShaderID);
        glDetachShader(m_RenderID,fragmentShaderID);

        //glDeleteShader(vertexShaderID);
        //glDeleteShader(fragmentShaderID);

        return m_RenderID;
    }
    Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader)
    {
        loadShaders(vertexShader, fragmentShader);
    }
    Shader::~Shader()
    {
        glDeleteProgram(m_RenderID);
    }
} // namespace

