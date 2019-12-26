/**
  * Created by Joscha Vack on 12/9/2019.
  *
  **/

#ifndef TS3PLUGINTEMPLATE2_LOGGER_H
#define TS3PLUGINTEMPLATE2_LOGGER_H

#include <spdlog/spdlog.h>

#include <teamspeak/public_definitions.h>


class Logger
{
private:
    static std::shared_ptr<spdlog::logger> coreLogger;  // logger for the core
    static std::shared_ptr<spdlog::logger> pluginLogger;      // logger for the plugin

public:
    static void init();

    static std::shared_ptr<spdlog::logger> createServerLogger(uint64 conId);

    static std::shared_ptr<spdlog::logger>& getCoreLogger() {
        return coreLogger;
    }

    static std::shared_ptr<spdlog::logger>& getLogger() {
        return pluginLogger;
    }
};

/** System logging **/

#define CORE_DEBUG(...)      Logger::getCoreLogger()->debug(__VA_ARGS__)
#define CORE_TRACE(...)      Logger::getCoreLogger()->trace(__VA_ARGS__)
#define CORE_INFO(...)       Logger::getCoreLogger()->info(__VA_ARGS__)
#define CORE_WARN(...)       Logger::getCoreLogger()->warn(__VA_ARGS__)
#define CORE_ERROR(...)      Logger::getCoreLogger()->error(__VA_ARGS__)
#define CORE_CRITICAL(...)   Logger::getCoreLogger()->critical(__VA_ARGS__)

/** User logging **/
#define LOG_DEBUG(...)      Logger::getLogger()->debug(__VA_ARGS__)
#define LOG_TRACE(...)      Logger::getLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)       Logger::getLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)       Logger::getLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)      Logger::getLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...)   Logger::getLogger()->critical(__VA_ARGS__)

#endif //TS3PLUGINTEMPLATE2_LOGGER_H
