#include <Dimon.h>
class DimonGame : public Dimon::Application
{
public:
	DimonGame() {};
	~DimonGame() {};
};

Dimon::Application* Dimon::CreateApplication() {
	return new DimonGame();
}