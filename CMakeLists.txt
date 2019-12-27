cmake_minimum_required(VERSION 3.15)
project(Ts3Tools)
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
    src/ui/Window.cpp
    src/ui/Window.h
    src/ui/UiThread.cpp src/ui/UiThread.h
    # -- glad -- #
    dependencies/glad/src/glad.c
    src/ui/Ui.h src/ui/Ui.cpp)

set(INCLUDES
    src/
    dependencies/glad/include
    dependencies/glfw/include
    dependencies/imgui
    dependencies/spdlog/include
    dependencies/ts3/include
    )


# add_subdirectory(dependencies/glad)
add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/imgui)
add_subdirectory(dependencies/spdlog)
add_subdirectory(dependencies/ts3)

add_definitions(-DGLFW_INCLUDE_NONE)
add_library(Ts3Tools SHARED ${FILES})
target_link_libraries(Ts3Tools PUBLIC glfw)
target_link_libraries(Ts3Tools PUBLIC imgui)
target_link_libraries(Ts3Tools PUBLIC spdlog)
target_include_directories(Ts3Tools PUBLIC ${INCLUDES})