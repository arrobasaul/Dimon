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

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		//void OnUpdate(/*Timestep ts*/) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& event);
		void Begin();
		void End();
		void  SetBlockEvents(bool block) { m_BlockEvents = block; }
		bool  GetBlockEvents() { return m_BlockEvents; }
	private:
		/*bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);*/
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};
}