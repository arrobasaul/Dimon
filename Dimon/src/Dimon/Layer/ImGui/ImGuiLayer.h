#pragma once
#include "Dimon/Events/KeyEvent.h"
#include "Dimon/Events/MouseEvent.h"
#include "Dimon/Events/ApplicationEvent.h"
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
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
	private:
		float m_Time = 0.0f;
	};
}