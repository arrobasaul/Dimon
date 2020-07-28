#include <iostream>
#include <Dimon.h>
#include <Dimon/Core/Entry.h>

#include "GameLayer.h"
class flappybird : public Dimon::Application
{
public:
	flappybird()
	{
		PushLayer(new GameLayer());
	}

	~flappybird()
	{
	}
};

Dimon::Application* Dimon::CreateApplication()
{
	return new flappybird();
}