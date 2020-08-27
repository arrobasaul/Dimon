#pragma once
#include "Dimon/Render/OrthographicCamera.h"
#include "Dimon/Util/TimeStep.h"
#include "Dimon/Events/ApplicationEvent.h"
#include "Dimon/Events/MouseEvent.h"

namespace Dimon {
	class OrthographicCameraController {
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnEvent(Event& e);
		void OnUpdate(TimeStep e);
		void OnResize(float width, float height);
		void SetZoomLevel(float zoomLevel) { m_ZoomLevel = zoomLevel; CalculateView();};
		float GetZoomLevel() { return m_ZoomLevel; };

		OrthographicCamera& GetCamera() { return m_Camera; };
		const OrthographicCamera& GetCamera() const { return m_Camera; };
	private:
		void CalculateView();
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		bool m_Rotation;
		OrthographicCamera m_Camera;

		glm::vec3 m_CameraProsition = { 0.0f,0.0f,0.0f };
		float m_CameraRotate = 0.0f, m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed =1.0f;
	};
}