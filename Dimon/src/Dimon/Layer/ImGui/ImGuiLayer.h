#pragma once
#include "Dimon/Layer/Layer.h"
namespace Dimon {
	class DIMON_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate(/*Timestep ts*/);
		void OnImGuiRender();
		void OnEvent(Event& event);
	private:
		float m_Time = 0.0f;
	};
}