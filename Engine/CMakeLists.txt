project( Engine )

set( GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE )

# add sub directories for projects with cmake support (currently glad, spdlog, GLFW)

add_subdirectory( vendor/glad )
add_subdirectory( vendor/spdlog )
add_subdirectory( vendor/glfw )

# source code
file(GLOB 
    SOURCES CONFIGURE_DEPENDS
        src/Engine/*.cpp 
        src/Engine/Rendering/*.cpp
        src/Engine/Rendering/Camera/*.cpp
        src/Engine/ImGui/*.cpp 
        src/Platform/OpenGL/*.cpp 
        src/Platform/GLFW/*.cpp 

        # stb_image
        vendor/stb_image/*.cpp

        # must compile and link imgui directly to project
        vendor/imgui/*.cpp
)

# library creation
add_library( Engine 
    STATIC 
        ${SOURCES}
)
target_link_libraries( Engine  
    PUBLIC
        GLAD
        glfw
        spdlog
)
target_precompile_headers( Engine 
    PUBLIC 
        EnginePCH.h
)
target_include_directories( Engine 
    PUBLIC 
        src 
        src/Engine 
        src/Platform

        vendor/imgui
        vendor/glm

        vendor/spdlog/include
    PRIVATE
        vendor/glfw/include
        vendor/glad/include
        vendor/stb_image
)