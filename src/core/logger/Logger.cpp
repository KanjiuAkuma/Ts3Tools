//
// Created by Joscha Vack on 11/29/2019.
//

#include "Logger.h"
#include <sstream>
#include <filesystem>

std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> Logger::core_console_sink;
std::shared_ptr<spdlog::sinks::basic_file_sink_mt> Logger::core_file_sink;

std::shared_ptr<spdlog::logger> Logger::coreLogger;
std::shared_ptr<spdlog::logger> Logger::pluginLogger;

void Logger::init()
{
    auto core_log_path = std::filesystem::current_path() / "Ts3Tools/logs/core.log";

    SetConsoleOutputCP(CP_UTF8);

    // log pattern
    spdlog::set_pattern("%^[%T] %n: %v%$");

    // core logger
    core_console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    core_console_sink->set_pattern("%^[%T] %n: %v%$");
    core_console_sink->set_level(spdlog::level::debug);

    core_file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(core_log_path.string(), false);
    core_file_sink->set_pattern("%^[%T] %n: %v%$");
    core_file_sink->set_level(spdlog::level::trace);

    coreLogger = std::make_shared<spdlog::logger>(spdlog::logger("CORE", {core_console_sink, core_file_sink}));
    coreLogger->set_level(spdlog::level::trace);
    coreLogger->debug("Core log path: {}", core_log_path.string());
    coreLogger->set_pattern("%^[%T] %n: %v%$");

    // todo: figure out how to ensure logs are flushed upon crash...
    coreLogger->flush_on(spdlog::level::trace);

    // client logger

    pluginLogger = spdlog::stdout_color_mt("Plugin");
    pluginLogger->set_level(spdlog::level::trace);
    pluginLogger->set_pattern("%^[%T] %n: %v%$");
}

std::shared_ptr<spdlog::logger> Logger::createServerLogger(uint64 conId) {

    std::shared_ptr<spdlog::logger> logger = spdlog::stdout_color_mt("CON " + std::to_string(conId));
    logger->set_level(spdlog::level::trace);
    logger->set_pattern("%^[%T] %n: %v%$");
    return logger;
}
