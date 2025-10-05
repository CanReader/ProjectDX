#pragma once

#include <memory>
#include <spdlog/spdlog.h>

#define DX_TRACE(...) SPDLOG_LOGGER_TRACE(Logger::GetLogger(),  __VA_ARGS__)
#define DX_INFO(...) SPDLOG_LOGGER_INFO(Logger::GetLogger(),  __VA_ARGS__)
#define DX_WARN(...) SPDLOG_LOGGER_WARN(Logger::GetLogger(), __VA_ARGS__)
#define DX_ERROR(...) SPDLOG_LOGGER_ERROR(Logger::GetLogger(),  __VA_ARGS__)
#define DX_FATAL(...) SPDLOG_LOGGER_CRITICAL(Logger::GetLogger(),  __VA_ARGS__)

class Logger
{
public:
	static void Initialize();

	static std::shared_ptr<spdlog::logger> GetLogger() { return logger; }

private:
	static std::shared_ptr<spdlog::logger> logger;
};

