#pragma once
#include "Dimon/Core.h"
#include <unordered_map>
namespace Dimon {
	class Shader {
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual const std::string& GetName() const = 0;

		static Ref<Shader> Create(const std::string& vertexShader, const std::string& fragmentShader);
		static Ref<Shader> Create(const std::string& name, const std::string& vertexShader, const std::string& fragmentShader);
	};
	class ShaderLibrery {
	public:
		void Add(const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& vertexShader, const std::string& fragmentShader);
		Ref<Shader> Load(const std::string& name, const std::string& vertexShader, const std::string& fragmentShader);

		Ref<Shader> Get(const std::string& name);
	private:

		std::unordered_map<std::string, Ref<Shader>> m_Shader;
	};
}