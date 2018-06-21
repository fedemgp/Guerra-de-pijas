cmake_minimum_required(VERSION 3.1.0)
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

message("Cargando fuentes para el editor")

# Find the QtWidgets library
find_package(Qt5Widgets)

message("[INFO] La raiz del proyecto es ${PROJECT_SOURCE_DIR}")

# Agrego ej3/include a la lista de directorios de includes
include_directories(${PROJECT_SOURCE_DIR}/src/editor/Editor)

# Esta macro toma cada uno los parámetros y ejecuta *uic* sobre ellos
# La aplicacion uic genera headers con la definición de los widgets
# a partir de un archivo .ui
# Los nombres de los headers generados se guardan en la variable pasada
# como primer parámetro.
# No, no los genera con la carpeta como prefijo.
qt5_wrap_ui(UIS_HEADERS
		src/editor/Editor/mainwindow.ui
		)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTORCC ON)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

message("Headers generados: ${UIS_HEADERS}")

file(GLOB EDITOR_SOURCES RELATIVE ${CMAKE_SOURCE_DIR}
		        "src/editor/Editor/*.cpp"
		        "src/editor/Editor/*.h"
		        "src/editor/Editor/resources.qrc")


# Tell CMake to create the helloworld executable
add_executable(editor ${EDITOR_SOURCES} ${UIS_HEADERS})
# Use the Widgets module from Qt 5
target_link_libraries(editor Qt5::Widgets)

## Instruct CMake to run moc automatically when needed
#set(CMAKE_AUTOMOC ON)
## Create code from a list of Qt designer ui files
#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTORCC ON)
#
## Find the QtWidgets library
#find_package(Qt5Widgets CONFIG REQUIRED)
#
#file(GLOB EDITOR_SOURCES RELATIVE ${CMAKE_SOURCE_DIR}
#        "src/editor/Editor/*.cpp"
#        "src/editor/Editor/*.h"
#        "src/editor/Editor/*.ui"
#        "src/editor/Editor/resources.qrc")
#
#
## Tell CMake to create the helloworld executable
#add_executable(editor ${EDITOR_SOURCES})
## Use the Widgets module from Qt 5
#target_link_libraries(editor Qt5::Widgets)



file(COPY assets DESTINATION ./)
