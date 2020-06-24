#include <Dimon.h>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "ImGui/imgui.h"
glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Model;
}
class ExampleLeyer : public Dimon::Layer {
public:
	ExampleLeyer()
		: Layer("Minecraf") {
		auto ca = camera(0.5f, { 0.6f,0.7f });
	}
	void OnUpdate() override {
	}
	void OnEvent(Dimon::Event& event) override {

		if (event.GetEventType() == Dimon::EventType::KeyPressed) {
			Dimon::KeyPressedEvent& e = (Dimon::KeyPressedEvent&)event;
			DM_CLIENT_INFO("{0}", (char)e.GetKeyCode());
		}
		//DM_CLIENT_TRACE("{0}", event);
	}
	virtual void OnImGuiRender() override {
		ImGui::Begin("Test");
		ImGui::Text("For Example");
		ImGui::End();
	}
};

class DimonGame : public Dimon::Application
{
public:
	DimonGame() { 
		PushLayer(new  ExampleLeyer()); 
	}
	~DimonGame() {};
};

Dimon::Application* Dimon::CreateApplication() {
	return new DimonGame();
}