cmake_minimum_required(VERSION 3.0)
project(4-Worms)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic -pthread")

message("Agregando '${CMAKE_SOURCE_DIR}/libs' como directorio de includes")
include_directories(${CMAKE_SOURCE_DIR}/libs)

file(GLOB CLIENT_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/client/*.cpp" "src/client/*.h" "libs/*.h" "libs/*.cpp")
add_executable(clients ${CLIENT_SOURCES} )
target_link_libraries(clients SDL2 SDL2_image SDL2_ttf SDL2_mixer)

message("Agregando Box2D como librería")
file(GLOB_RECURSE BOX2D_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "libs/Box2D/*.cpp" "libs/Box2D/*.h")
add_library(Box2D STATIC ${BOX2D_SOURCES})

message("Cargando fuentes para el servidor")
file(GLOB SERVER_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/server/*.cpp" "src/server/*.h")
file(GLOB SERVER_LIBS_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} 
	"libs/Chronometer.*"
	"libs/CommunicationSocket.*"
	"libs/DoubleBuffer.*"
	"libs/ErrorMessages.*"
	"libs/Exception.*"
	"libs/GameStateMsg.*"
	"libs/Point.*"
	"libs/Socket.*"
	"libs/Stage.*"
	"libs/Stream.*"
	"libs/utils.*")
add_executable(server
        ${SERVER_SOURCES}
        ${SERVER_LIBS_SOURCES})

target_link_libraries(server Box2D)
file(COPY assets DESTINATION ./)
