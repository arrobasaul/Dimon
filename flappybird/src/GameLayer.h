#pragma once

#include "Dimon.h"

#include "Level.h"
#include <imgui/imgui.h>

class GameLayer : public Dimon::Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Dimon::TimeStep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Dimon::Event& e) override;
	bool OnMouseButtonPressed(Dimon::MouseButtonPressedEvent& e);
	bool OnWindowResize(Dimon::WindowResizeEvent& e);
private:
	void CreateCamera(uint32_t width, uint32_t height);
private:
	Dimon::Scope<Dimon::OrthographicCamera> m_Camera;
	Level m_Level;
	ImFont* m_Font;
	float m_Time = 0.0f;
	bool m_Blink = false;

	enum class GameState
	{
		Play = 0, MainMenu = 1, GameOver = 2
	};

	GameState m_State = GameState::MainMenu;
};