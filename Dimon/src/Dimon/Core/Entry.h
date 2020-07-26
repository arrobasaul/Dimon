#pragma once
#include "Dimon/Core/Core.h"
#ifdef DM_PLATFORM_WINDOWS
extern Dimon::Application* Dimon::CreateApplication();

int main(int argc, char** argv)
{
	Dimon::Log::Init();

	DM_PROFILE_BEGIN_SESSION("init", "dimon-init.json");
	auto app = Dimon::CreateApplication();
	DM_PROFILE_END_SESSION();

	DM_PROFILE_BEGIN_SESSION("run", "dimon-run.json");
	app->Run();
	DM_PROFILE_END_SESSION();

	DM_PROFILE_BEGIN_SESSION("run", "dimon-shotpdown.json");
	delete app;
	DM_PROFILE_END_SESSION();
}
#endif // DM_PLATFORM_WINDOWS

