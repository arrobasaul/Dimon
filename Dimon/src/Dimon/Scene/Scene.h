#pragma once
#include "entt.hpp"
namespace Dimon {
	class Scene
	{
	public:
		Scene();
		~Scene();
	private:
		entt::registry m_Registry;
	};

}

