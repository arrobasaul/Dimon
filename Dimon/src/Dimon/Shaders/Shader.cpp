#include "dmpch.h"

#include "Shader.h"
#include "Dimon/Util/FileUtil.h"
#include "Dimon/Log.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "Dimon/Render/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Dimon {
    Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexShader, const std::string& fragmentShader)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:		DM_CORE_ASSERT(false, "RendererAPI::None no supported"); return nullptr;
        case RendererAPI::API::OpenGL:		return std::make_shared<OpenGLShader>(name, vertexShader, fragmentShader);
        default:
            break;
        }
        DM_CORE_ASSERT(false, "UnKnown");
        return nullptr;
    }
    Ref<Shader> Shader::Create(const std::string& vertexShader, const std::string& fragmentShader)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:		DM_CORE_ASSERT(false, "RendererAPI::None no supported"); return nullptr;
        case RendererAPI::API::OpenGL:		return std::make_shared<OpenGLShader>(vertexShader, fragmentShader);
        default:
            break;
        }
        DM_CORE_ASSERT(false, "UnKnown");
        return nullptr;
    }
    /*uint32_t Shader::compileShader(const char* source, uint32_t shaderType)
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
    }*/

    /*uint32_t Shader::linkProgram(uint32_t vertexShaderID, uint32_t fragmentShaderID)
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
    }*/
    void ShaderLibrery::Add(const Ref<Shader>& shader)
    {
        auto name = shader->GetName();
        DM_CORE_ASSERT(m_Shader.find(name) == m_Shader.end(), "Shader already exist");
        m_Shader[name] = shader;
    }
    Ref<Shader> ShaderLibrery::Load(const std::string& vertexShader, const std::string& fragmentShader)
    {
        auto shader = Shader::Create(vertexShader, fragmentShader);
        Add(shader);
        return shader;
    }
    Ref<Shader> ShaderLibrery::Load(const std::string& name, const std::string& vertexShader, const std::string& fragmentShader)
    {
        auto shader = Shader::Create(name, vertexShader, fragmentShader);
        Add(shader);
        return shader;
    }
    Ref<Shader> ShaderLibrery::Get(const std::string& name)
    {
        DM_CORE_ASSERT(m_Shader.find(name) != m_Shader.end(), "Shader not found");
        return m_Shader[name];
    }
} // namespace

