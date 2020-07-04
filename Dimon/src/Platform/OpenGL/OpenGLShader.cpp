#include "dmpch.h"

#include "OpenGLShader.h"
#include "Dimon/Util/FileUtil.h"
#include "Dimon/Log.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Dimon {
    uint32_t OpenGLShader::compileShader(const char* source, uint32_t shaderType)
    {
        auto shaderID = glCreateShader(shaderType);

        glShaderSource(shaderID, 1, &source, 0);
        glCompileShader(shaderID);

        GLint isSuccess = 0;
        //GLchar infoLog[512];

        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isSuccess);
        if (!isSuccess) {//if (isSuccess==GL_FALSE) {
            GLint MaxLength = 0;
            glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &MaxLength);
            std::vector<GLchar> infoLog(MaxLength);

            glGetShaderInfoLog(shaderID, MaxLength, nullptr, &infoLog[0]);

            DM_CORE_ERROR("Unable to load a shader: {0}", infoLog[0]);
            DM_CORE_ASSERT(false, "Shader link faild");
            glDeleteShader(shaderID);
            //throw std::runtime_error("Unable to load a shader: " + std::string(infoLog));
        }

        return shaderID;
    }

    uint32_t OpenGLShader::linkProgram(uint32_t vertexShaderID, uint32_t fragmentShaderID)
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
            DM_CORE_ERROR("Unable to load a Program: {0}", infoLog);
            //throw std::runtime_error("Unable to load a shader: " + std::string(infoLog));
            glDeleteProgram(program);
            glDeleteShader(vertexShaderID);
            glDeleteShader(fragmentShaderID);
        }
        return program;
    }
    void OpenGLShader::Bind() const
    {
        glUseProgram(m_RenderID);
    }
    void OpenGLShader::UnBind() const
    {
        glUseProgram(0);
    }
    void OpenGLShader::SetUniformMat3(const std::string& name, const glm::mat3& matrix)
    {
        GLint uniform = glGetUniformLocation(m_RenderID, name.c_str());
        glUniformMatrix3fv(uniform, 1, GL_FALSE, glm::value_ptr(matrix));
    }
    void OpenGLShader::SetUniformMat4(const std::string& name, const glm::mat4& matrix)
    {
        GLint uniform = glGetUniformLocation(m_RenderID, name.c_str());
        glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(matrix));

    }
    void OpenGLShader::SetUniformInt(const std::string& name, int value)
    {
        GLint location = glGetUniformLocation(m_RenderID, name.c_str());
        glUniform1i(location, value);
    }
    void OpenGLShader::SetUniformFloat(const std::string& name, const float& value)
    {
        GLint location = glGetUniformLocation(m_RenderID, name.c_str());
        glUniform1f(location, value);
    }
    void OpenGLShader::SetUniformFloat2(const std::string& name, const glm::vec2& value)
    {
        GLint location = glGetUniformLocation(m_RenderID, name.c_str());
        glUniform2f(location, value.r, value.g);
    }
    void OpenGLShader::SetUniformFloat3(const std::string& name, const glm::vec3& value)
    {
        GLint location = glGetUniformLocation(m_RenderID, name.c_str());
        glUniform3f(location, value.r, value.g, value.b);
    }
    void OpenGLShader::SetUniformFloat4(const std::string& name, const glm::vec4& value)
    {
        GLint location = glGetUniformLocation(m_RenderID, name.c_str());
        glUniform4f(location, value.r, value.g, value.b, value.a);
    }
    uint32_t OpenGLShader::loadShaders(const std::string& name, const std::string& vertexShader, const std::string& fragmentShader)
    {
        m_Name = name;
        auto vertexSource = getFileContents(vertexShader);
        auto fragmentSource = getFileContents(fragmentShader);

        auto vertexShaderID = compileShader(vertexSource.c_str(), GL_VERTEX_SHADER);
        auto fragmentShaderID = compileShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER);

        m_RenderID = linkProgram(vertexShaderID, fragmentShaderID);

        glDetachShader(m_RenderID, vertexShaderID);
        glDetachShader(m_RenderID, fragmentShaderID);

        //glDeleteShader(vertexShaderID);
        //glDeleteShader(fragmentShaderID);

        return m_RenderID;
    }
    uint32_t OpenGLShader::loadShaders(const std::string& vertexShader, const std::string& fragmentShader)
    {
        //D:/Code/c++/OpenGLRoot/Dimon/DimonGame/
        auto lastSlash = vertexShader.find_first_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        auto lastDot = vertexShader.rfind('.');
        auto count = lastDot == std::string::npos ? vertexShader.size() - lastSlash : lastDot - lastSlash;
        m_Name = vertexShader.substr(lastSlash, lastDot);

        auto vertexSource = getFileContents(vertexShader);
        auto fragmentSource = getFileContents(fragmentShader);

        auto vertexShaderID = compileShader(vertexSource.c_str(), GL_VERTEX_SHADER);
        auto fragmentShaderID = compileShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER);

        m_RenderID = linkProgram(vertexShaderID, fragmentShaderID);

        glDetachShader(m_RenderID, vertexShaderID);
        glDetachShader(m_RenderID, fragmentShaderID);

        //glDeleteShader(vertexShaderID);
        //glDeleteShader(fragmentShaderID);

        return m_RenderID;
    }
    OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexShader, const std::string& fragmentShader)
        :m_Name(name)
    {
        loadShaders(name, vertexShader, fragmentShader);
    }
    OpenGLShader::OpenGLShader(const std::string& vertexShader, const std::string& fragmentShader)
    {
        loadShaders(vertexShader, fragmentShader);
    }
    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_RenderID);
    }
} // namespace

