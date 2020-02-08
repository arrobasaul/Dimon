#pragma once
#ifdef DM_PLATFORM_WINDOWS
extern Dimon::Application* Dimon::CreateApplication();

int main(int argc, char** argv)
{
	printf("Entry to Engine Dimon");
	auto app = Dimon::CreateApplication();
	app->Run();
	delete app;
}
#endif // DM_PLATFORM_WINDOWS

