cmake_minimum_required (VERSION 3.0)
set (CMAKE_CXX_STANDARD 17)

project (GameEngine2D)
add_subdirectory(Engine/vendor/include/glad)

# libraries
link_directories(Engine/vendor/lib)

set (PROJECT_LINK_LIBS libspdlog.a libglfw.3.dylib GLAD)

# source code
file(GLOB SOURCES Engine/src/Core/*.cpp Engine/src/Core/ImGui/*.cpp Engine/src/Platform/OpenGL/*.cpp Engine/src/Platform/Window/*.cpp Engine/vendor/include/imgui/*.cpp)

# headers
include_directories(Engine/src/Core Engine/src/Platform Engine/vendor/include Engine/vendor/include/glad/include)

add_executable(GameEngine2D ${SOURCES})
target_link_libraries(GameEngine2D ${PROJECT_LINK_LIBS})
target_precompile_headers(GameEngine2D PRIVATE Engine/EnginePCH.h)