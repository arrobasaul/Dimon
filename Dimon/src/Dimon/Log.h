#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"


namespace Dimon {
	class DIMON_API Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}
#define DM_CORE_TRACE(...)		::Dimon::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define DM_CORE_INFO(...)		::Dimon::Log::GetCoreLogger()->info(__VA_ARGS__)
#define DM_CORE_ERROR(...)		::Dimon::Log::GetCoreLogger()->error(__VA_ARGS__)
#define DM_CORE_WARM(...)		::Dimon::Log::GetCoreLogger()->warn(__VA_ARGS__)

#define DM_CLIENT_TRACE(...)	::Dimon::Log::GetClientLogger()->trace(__VA_ARGS__)
#define DM_CLIENT_INFO(...)		::Dimon::Log::GetClientLogger()->info(__VA_ARGS__)
#define DM_CLIENT_ERROR(...)	::Dimon::Log::GetClientLogger()->error(__VA_ARGS__)
#define DM_CLIENT_WARM(...)		::Dimon::Log::GetClientLogger()->warm(__VA_ARGS__)