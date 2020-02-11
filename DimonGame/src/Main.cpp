#include <Dimon.h>
class ExampleLeyer : public Dimon::Layer {
public:
	ExampleLeyer()
		: Layer("Minecraf") {
	}
	void OnUpdate() override {
		DM_CLIENT_INFO("ExampleLeyer::Update");
	}
	void OnEvent(Dimon::Event& event) override {
		DM_CLIENT_TRACE("{0}", event);
	}
};

class DimonGame : public Dimon::Application
{
public:
	DimonGame() { 
		PushLayer(new  ExampleLeyer()); 
		PushOverlay(new Dimon::ImGuiLayer());
	}
	~DimonGame() {};
};

Dimon::Application* Dimon::CreateApplication() {
	return new DimonGame();
}