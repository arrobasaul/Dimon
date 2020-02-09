#pragma once
#ifdef DM_PLATFORM_WINDOWS
	#ifdef DM_BUILD_DLL
		#define DIMON_API __declspec(dllexport)
	#else
		#define DIMON_API __declspec(dllimport)
	#endif
#else
	#error Dimon only support windows! more and less!!
#endif // DM_PLATFORM_WINDOWS

#define BIT(x) (1 << x)