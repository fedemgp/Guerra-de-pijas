cmake_minimum_required(VERSION 3.0)
project(4-Worms)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic -pthread")

message("Agregando '${CMAKE_SOURCE_DIR}/libs' como directorio de includes")
include_directories(${CMAKE_SOURCE_DIR}/libs)

message("Agregando Box2D como librería")
file(GLOB_RECURSE BOX2D_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "libs/Box2D/*.cpp")
add_library(Box2D STATIC ${BOX2D_SOURCES})

add_executable( client
        libs/CommunicationSocket.cpp
        libs/CommunicationSocket.h
        libs/ErrorMessages.h
        libs/Exception.cpp
        libs/Exception.h
        libs/Socket.cpp
        libs/Socket.h
        src/client/ClientSocket.cpp
        src/client/ClientSocket.h
        src/client/main.cpp)
target_link_libraries(client SDL2 SDL2_image)

add_executable(	server
        libs/CommunicationSocket.cpp
        libs/CommunicationSocket.h
        libs/ErrorMessages.h
        libs/Exception.cpp
        libs/Exception.h
        libs/Socket.cpp
        libs/Socket.h
        src/server/main.cpp
        src/server/ServerSocket.cpp
        src/server/ServerSocket.h)
target_link_libraries(server Box2D)

file(GLOB_RECURSE CLIENT_SERVER_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/clientServer/*.cpp" "src/clientServer/*.h" "libs/*.h" "libs/*.cpp")
add_executable( clientServer
        ${CLIENT_SERVER_SOURCES} src/clientServer/server/GameTeams.cpp src/clientServer/server/GameTeams.h src/clientServer/server/Team.cpp src/clientServer/server/Team.h src/clientServer/server/Falling.cpp src/clientServer/server/Falling.h src/clientServer/client/Falling.cpp src/clientServer/client/Falling.h src/clientServer/server/Land.cpp src/clientServer/server/Land.h src/clientServer/client/Land.cpp src/clientServer/client/Land.h)

target_link_libraries(clientServer Box2D SDL2 SDL2_image SDL2_ttf)