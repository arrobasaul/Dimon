#pragma once

#include <memory>
#ifdef DM_PLATFORM_WINDOWS
	#if DM_DYNAMIC_LINK
		#ifdef DM_BUILD_DLL
			#define DIMON_API __declspec(dllexport)
		#else
			#define DIMON_API __declspec(dllimport)
		#endif
	#else
		#define DIMON_API
	#endif
#else
	#error Dimon only support windows! more and less!!
#endif // DM_PLATFORM_WINDOWS

#ifdef DM_DEBUG
	#define DM_ENABLE_ASSERTS2
#endif // DM_DEBUG

#ifdef DM_ENABLE_ASSERTS
	#define DM_CLIENT_ASSERT(x, ...) { if(!(x)) { DM_CLIENT_ERROR("Assertion Faild: {0}", __VA_ARGS__); __debugbreak(); } }
	#define DM_CORE_ASSERT(x, ...) { if(!(x)) { DM_CORE_ERROR("Assertion Faild: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define DM_CLIENT_ASSERT(x, ...)
	#define DM_CORE_ASSERT(x, ...)
#endif // DM_ENABLE_ASSERTS

#define DM_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#define BIT(x) (1 << x)

namespace Dimon {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}