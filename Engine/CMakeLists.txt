project (GameEngine2D)

# add sub directories for projects with cmake support (currently glad, spdlog, GLFW)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/GLFW)

# source code
file(GLOB 
    SOURCES 
        src/Engine/*.cpp 
        src/Engine/ImGui/*.cpp 
        src/Platform/OpenGL/*.cpp 
        src/Platform/GLFW/*.cpp 

        # must compile and link imgui directly to project
        vendor/imgui/*.cpp
)

# library creation
add_library(GameEngine2D 
    SHARED 
        ${SOURCES}
)
target_link_libraries(GameEngine2D  
    PRIVATE
        GLAD
        GLFW
        spdlog
)
target_precompile_headers(GameEngine2D 
    PUBLIC 
        EnginePCH.h
)
target_include_directories(GameEngine2D 
    PUBLIC 
        src 
        src/Engine 
        src/Platform

        vendor/glm

    PRIVATE
        vendor/spdlog/include
        vendor/GLFW/include
        vendor/glad/include
        vendor  
)