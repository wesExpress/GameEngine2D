cmake_minimum_required (VERSION 3.0)
project (GameEngine2D)

set (CMAKE_CXX_STANDARD 17)

# headers
include_directories(Engine/vendor/include)

set (PROJECT_LINK_LIBS libspdlog.a libglfw.dylib)
link_directories(Engine/vendor/lib)

# source code
file(GLOB SOURCES "Engine/src/*.cpp")

add_executable(GameEngine2D ${SOURCES})
target_link_libraries(GameEngine2D ${PROJECT_LINK_LIBS})