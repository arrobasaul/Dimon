#pragma once
#ifdef DM_PLATFORM_WINDOWS
extern Dimon::Application* Dimon::CreateApplication();

int main(int argc, char** argv)
{
	Dimon::Log::Init();
	//Dimon::Log::GetCoreLogger()->warn("Iniciailze log");
	//Dimon::Log::GetCoreLogger()->info("Hello");
	DM_CORE_TRACE("ERROR AL INICIAR");
	auto app = Dimon::CreateApplication();
	DM_CORE_WARM("mensaje");
	app->Run();
	delete app;
}
#endif // DM_PLATFORM_WINDOWS

