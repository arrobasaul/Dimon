#include "dmpch.h"
#include "Scene.h"
#include "glm/glm.hpp"
namespace Dimon {
	static void DoMath(const glm::mat4& transform) {

	}
	Scene::Scene()
	{
		struct  TransformComponent {
			glm::mat4 Transform;

			TransformComponent() = default;
			TransformComponent(const TransformComponent&) = default;
			TransformComponent(const glm::mat4& transform)
				: Transform(transform){}

			operator glm::mat4()& { return Transform; }
			operator const glm::mat4& () { return Transform; }
		};
		TransformComponent transform;
		DoMath(transform);
		entt::entity entt = m_Registry.create();
	}
	Scene::~Scene()
	{
	}
}