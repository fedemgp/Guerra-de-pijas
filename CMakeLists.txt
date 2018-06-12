cmake_minimum_required(VERSION 3.0)
project(4-Worms)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic -pthread")

message("Agregando '${CMAKE_SOURCE_DIR}/libs' como directorio de includes")
include_directories(${CMAKE_SOURCE_DIR}/libs)

message("Agregando Box2D como librería")
file(GLOB_RECURSE BOX2D_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "libs/Box2D/*.cpp")
add_library(Box2D STATIC ${BOX2D_SOURCES})

message("Cargando fuentes para el cliente")
file(GLOB CLIENT_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/client/*.cpp" "src/client/*.h" "libs/*.cpp" "libs/*.h")
add_executable( client ${CLIENT_SOURCES})
target_link_libraries(client SDL2 SDL2_image SDL2_ttf SDL2_mixer)


message("Cargando fuentes para el servidor")
file(GLOB SERVER_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/server/*.cpp" "src/server/*.h")
file(GLOB SERVER_LIBS_SOURCES RELATIVE ${CMAKE_SOURCE_DIR}
		"libs/Chronometer.*" 
		"libs/CommunicationSocket.*"
		"libs/DoubleBuffer.h"
		"libs/ErrorMessages.h"
		"libs/Exception.*"
		"libs/GameStateMsg.h"
		"libs/Point.h"
		"libs/Socket.*"
		"libs/Stage.*"
		"libs/Stream.h"
		"libs/utils.h")
add_executable(	server ${SERVER_SOURCES} ${SERVER_LIBS_SOURCES})
target_link_libraries(server Box2D)

message("Preparando directivas de instalación")
file(COPY assets DESTINATION ./)

#file(GLOB_RECURSE CLIENT_SERVER_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/clientServer/*.cpp" "src/clientServer/*.h" "libs/*.h" "libs/*.cpp")
#add_executable( clientServer
#        ${CLIENT_SERVER_SOURCES})
#
#target_link_libraries(clientServer Box2D SDL2 SDL2_image SDL2_ttf)