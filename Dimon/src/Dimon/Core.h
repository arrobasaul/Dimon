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

#ifdef DM_ENABLE_ASSERTS
	#define DM_ASSERT(x, ...) { if(!(x)) { DM_CLIENT_ERROR("Assertion Faild: {0}", __VA_ARGS__); __debugbreak(); } }
	#define DM_CORE_ASSERT(x, ...) { if(!(x)) { DM_CORE_ERROR("Assertion Faild: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define DM_ASSERT(x, ...)
	#define DM_CORE_ASSERT(x, ...)
#endif // DM_ENABLE_ASSERTS


#define BIT(x) (1 << x)