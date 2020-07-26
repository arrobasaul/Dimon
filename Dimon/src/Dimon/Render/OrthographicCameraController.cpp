#include "dmpch.h"
#include "OrthographicCameraController.h"
#include "Dimon/Core/CoreInput.h"
#include "Dimon/Core/KeyCodes.h"
namespace Dimon {
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		:m_AspectRatio(aspectRatio), m_Rotation(rotation), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel,-m_ZoomLevel, m_ZoomLevel)
	{
	}
	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispacher(e);
		dispacher.Dispatch<MouseScrolledEvent>(DM_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispacher.Dispatch<WindowResizeEvent>(DM_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}
	void OrthographicCameraController::OnUpdate(TimeStep timeStep)
	{
		if (CoreInput::IsKeyPressed(DM_KEY_A)) {
			m_CameraProsition.x -= m_CameraTranslationSpeed * timeStep;
		}
		else if (CoreInput::IsKeyPressed(DM_KEY_D)) {
			m_CameraProsition.x += m_CameraTranslationSpeed * timeStep;
		}

		if (CoreInput::IsKeyPressed(DM_KEY_W)) {
			m_CameraProsition.y += m_CameraTranslationSpeed * timeStep;
		}
		else if (CoreInput::IsKeyPressed(DM_KEY_S)) {
			m_CameraProsition.y -= m_CameraTranslationSpeed * timeStep;
		}
		if (m_Rotation) {
			if (CoreInput::IsKeyPressed(DM_KEY_Q)) {
				m_CameraRotate += m_CameraRotationSpeed * timeStep;
			}
			else if (CoreInput::IsKeyPressed(DM_KEY_E)) {
				m_CameraRotate -= m_CameraRotationSpeed * timeStep;
			}
			m_Camera.SetRotation(m_CameraRotate);
		}
		
		m_Camera.SetPosition(m_CameraProsition);
	}
	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() *0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);

		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
}