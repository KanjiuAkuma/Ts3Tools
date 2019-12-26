cmake_minimum_required(VERSION 3.15)
set(PROJECT Ts3Tools)

project(${PROJECT})
set(CMAKE_CXX_STANDARD 20)

set(FILES
    src/Plugin.h
    src/Plugin.cpp
    src/GlobalDefinitions.h
    src/GlobalDefinitions.cpp
    src/util/Util.h
    src/util/Util.cpp
    src/core/Core.h
    src/core/logger/Logger.h
    src/core/logger/Logger.cpp
    src/core/server/Server.h
    src/core/server/Server.cpp
    src/core/server/ServerList.h
    src/core/server/ServerList.cpp
    src/core/channel/Channel.h
    src/core/channel/Channel.cpp
    src/core/channel/ChannelList.h
    src/core/channel/ChannelList.cpp
    src/core/client/Client.h
    src/core/client/Client.cpp
    src/core/client/ClientList.h
    src/core/client/ClientList.cpp
    src/util/Random.h
    src/util/Random.cpp
    )

set(INCLUDES
    src/
    dependencies/ts3/include
    dependencies/spdlog/include)

add_subdirectory(dependencies/ts3)
add_subdirectory(dependencies/spdlog)

add_library(${PROJECT} SHARED ${FILES})
include_directories(${PROJECT_NAME} PRIVATE ${INCLUDES})