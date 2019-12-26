#pragma once

/**
  * Created by Joscha Vack on 12/26/2019.
  *
  **/

#ifdef NDEBUG
    #define BUILD
#else
    #define BUILD "-- debug"
#endif

/** Plugin info **/
#define PLUGIN_NAME "Ts3 Tools" BUILD
#define PLUGIN_VERSION "1.0" BUILD
#define PLUGIN_AUTHOR "Kanjiu Akuma" BUILD
#define PLUGIN_DESCRIPTION "Ts3 Utility Plugin\n" BUILD\
                           "[B]Feature List:[/B]\n"\
                           "    - None as of now."
#define PLUGIN_COMMAND_PREFIX "T"

/** Custom Macros **/

#include "core/logger/Logger.h"
#include <teamspeak/public_errors.h>

#ifdef NDEBUG
#define ASSERT(v)
#define WARN
#define ERR(x) throw std::runtime_error("Error: Failed to execute '" + #x + "' in function " + __FUNCTION__  + ".")
#else
#define ASSERT(v) if (!(v)) {LOG_WARN("Assertion failed: '{}' in function {}", #v, __FUNCTION__); __debugbreak();}
#define WARN __debugbreak();
#define ERR(x) __debugbreak()
#endif

#define VALIDATE(f) {auto _r = f; if(_r != ERROR_ok) {LOG_WARN("Failed to execute '{}' in function {}. Error: 0x{:04x}", #f, __FUNCTION__, _r); WARN;}}
#define REQUIRE(f) {auto _r = f; if(_r != ERROR_ok) {LOG_CRITICAL("Failed to execute '{}' in function {}. Error: 0x{:04x}", #f, __FUNCTION__, _r); ERR(f);}}
#define CORE_VALIDATE(f) {auto _r = f; if(_r != ERROR_ok) {CORE_WARN("Failed to execute '{}' in function {}. Error: 0x{:04x}", #f, __FUNCTION__, _r); WARN;}}
#define CORE_REQUIRE(f) {auto _r = f; if(_r != ERROR_ok) {CORE_CRITICAL("Failed to execute '{}' in function {}. Error: 0x{:04x}", #f, __FUNCTION__, _r); ERR(f);}}

#define TS3_CALLBACK CORE_TRACE("{}", __FUNCTION__)
#define TS3_CALLBACK_ARG(x, ...) CORE_TRACE("{}: " x, __FUNCTION__, __VA_ARGS__)

/** Ts3 Macros **/

#define PLUGIN_API_VERSION 23
#define _strcpy(dest, destSize, src) strcpy_s(dest, destSize, src)
#define PLUGINS_EXPORTDLL __declspec(dllexport)