#include "ptapch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"
namespace Pinata {

	 Ref<spdlog::logger> Log::s_CoreLogger;
	 Ref<spdlog::logger> Log::s_ClientLogger;

	 void Log::Init()
	 {
		 spdlog::set_pattern("%^[%T] %n: %v%$");
		 s_CoreLogger = spdlog::stdout_color_mt("PINATA");
		 s_CoreLogger->set_level(spdlog::level::trace);

		 s_ClientLogger = spdlog::stderr_color_mt("APP");
		 s_ClientLogger->set_level(spdlog::level::trace);


	 }

}