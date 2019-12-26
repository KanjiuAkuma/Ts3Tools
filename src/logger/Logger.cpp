//
// Created by Joscha Vack on 11/29/2019.
//

#include "Logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <sstream>

std::shared_ptr<spdlog::logger> Logger::coreLogger;
std::shared_ptr<spdlog::logger> Logger::pluginLogger;

void Logger::init()
{
    SetConsoleOutputCP(CP_UTF8);

    // log pattern
    spdlog::set_pattern("%^[%T] %n: %v%$");

    // core logger
    coreLogger = spdlog::stdout_color_mt("CORE");
    coreLogger->set_level(spdlog::level::trace);
    coreLogger->debug("Initialized core log system");

    pluginLogger = spdlog::stdout_color_mt("PLUGIN");
    pluginLogger->set_level(spdlog::level::trace);
    pluginLogger->debug("Initialized plugin log system");
}

std::shared_ptr<spdlog::logger> Logger::createServerLogger(uint64 conId) {
    std::shared_ptr<spdlog::logger> logger = spdlog::stdout_color_mt("CON " + std::to_string(conId));
    logger->set_level(spdlog::level::trace);
    return logger;
}
