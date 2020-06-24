#pragma once

namespace Dimon {
	class Shader {
	public:
		void Bind() const;
		void UnBind() const;
		
		Shader(const std::string& vertexShader, const std::string& fragmentShader);
		~Shader();
	private:
		uint32_t loadShaders(const std::string& vertexShader, const std::string& fragmentShader);
		uint32_t compileShader(const char* source, uint32_t shaderType);
		uint32_t linkProgram(uint32_t vertexShaderID, uint32_t fragmentShaderID);
		uint32_t m_RenderID;
	};
	
}