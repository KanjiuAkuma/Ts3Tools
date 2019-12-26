cmake_minimum_required(VERSION 3.15)
set(PROJECT Ts3Tools)

project(${PROJECT})
set(CMAKE_CXX_STANDARD 20)

set(INCLUDES src/)

set(FILES
        src/Macros.h
        src/Plugin.h
        src/Plugin.cpp
        src/GlobalDefinitions.h
        src/GlobalDefinitions.cpp
        src/util/Util.h
        src/util/Util.cpp
        src/logger/Logger.h
        src/logger/Logger.cpp
        src/base/server/Server.h
        src/base/server/Server.cpp
        src/base/server/ServerList.h
        src/base/server/ServerList.cpp
        src/base/channel/Channel.h
        src/base/channel/Channel.cpp
        src/base/channel/ChannelList.h
        src/base/channel/ChannelList.cpp
        src/base/client/Client.h
        src/base/client/Client.cpp
        src/base/client/ClientList.h
        src/base/client/ClientList.cpp
        src/util/Random.h
        src/util/Random.cpp
        )

add_subdirectory(dependencies/ts3)
add_subdirectory(dependencies/spdlog)

add_library(${PROJECT} SHARED ${FILES})
include_directories(${PROJECT_NAME} PRIVATE ${INCLUDES})