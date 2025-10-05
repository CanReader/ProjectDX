#include "Logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/msvc_sink.h>
#include <spdlog/async.h>

std::shared_ptr<spdlog::logger> Logger::logger;

void Logger::Initialize()
{
	constexpr size_t log_queue_size = 8192;
	constexpr size_t num_threads = 1;

	spdlog::init_thread_pool(log_queue_size,num_threads);

	std::vector<spdlog::sink_ptr> sinks;

	sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
	sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>("DirectX.log",1024*1024*10,5));
	sinks.push_back(std::make_shared<spdlog::sinks::msvc_sink_mt>());

	sinks[0]->set_pattern("%^[%T] [%l] (%s:%#) -> %v %$");
	sinks[1]->set_pattern("[%T] [%l] (%#) %s:%! -> %v");
	sinks[2]->set_pattern("\n\n[%T] [%l] (%#) %s:%! -> %v\n\n");

	logger = std::make_shared<spdlog::async_logger>("ENGINE",sinks.begin(),sinks.end(),spdlog::thread_pool(),spdlog::async_overflow_policy::block);

	logger->set_level(spdlog::level::trace);
	logger->flush_on(spdlog::level::warn);
	spdlog::register_logger(logger);
}
