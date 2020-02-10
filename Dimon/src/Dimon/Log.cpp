#include "dmpch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"
namespace Dimon {
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init() {
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("DIMON");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);

		/*spdlog::logger logger("multi_sink", { s_CoreLogeger, s_ClientLogeger });
		logger.warn("this should appear in both console and file");
		logger.info("this message should not appear in the console, only in the file");
		*/
		/*auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		console_sink->set_level(spdlog::level::warn);
		console_sink->set_pattern("[multi_sink_example] [%^%l%$] %v");

		auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/multisink.txt", true);
		file_sink->set_level(spdlog::level::trace);

		auto Log::s_Logger = spdlog::logger("multi_sink", { s_CoreLogger, s_ClientLogger });

		s_Logger.set_level(spdlog::level::debug);
		s_Logger.warn("this should appear in both console and file");
		s_Logger.info("this message should not appear in the console, only in the file");*/
	}
}
