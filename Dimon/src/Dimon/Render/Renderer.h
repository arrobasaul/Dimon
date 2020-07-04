#pragma once
#include "RendererAPI.h"
#include "Dimon/Shaders/Shader.h"
#include "OrthographicCamera.h"
#include <glm/glm.hpp>
namespace Dimon {

	class Renderer {

	public:
		static void Init();
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct DataScene {
			glm::mat4 ViewProjectionMatrix;
		};

		static DataScene* m_DataScene;
	};
}