#pragma once
#include "glm/glm.hpp"
#include "Dimon/Shaders/Shader.h"
namespace Dimon {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& name, const std::string& vertexShader, const std::string& fragmentShader);
		OpenGLShader(const std::string& vertexShader, const std::string& fragmentShader);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual const std::string& GetName() const override { return m_Name; };
		void SetUniformMat3(const std::string& name, const glm::mat3& matrix);
		void SetUniformMat4(const std::string& name, const glm::mat4& matrix);

		void SetUniformInt(const std::string& name, int value);

		void SetUniformFloat(const std::string& name, const float& value);
		void SetUniformFloat2(const std::string& name, const glm::vec2& value);
		void SetUniformFloat3(const std::string& name, const glm::vec3& value);
		void SetUniformFloat4(const std::string& name, const glm::vec4& value);
	private:
		uint32_t loadShaders(const std::string& name, const std::string& vertexShader, const std::string& fragmentShader);
		uint32_t loadShaders(const std::string& vertexShader, const std::string& fragmentShader);
		uint32_t compileShader(const char* source, uint32_t shaderType);
		uint32_t linkProgram(uint32_t vertexShaderID, uint32_t fragmentShaderID);
		uint32_t m_RenderID;
		std::string m_Name;
	};

}