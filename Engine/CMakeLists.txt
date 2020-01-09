project (GameEngine2D)
add_subdirectory(vendor/include/glad)

# source code
file(GLOB 
    SOURCES 
        src/Engine/*.cpp 
        src/Engine/ImGui/*.cpp 
        src/Platform/OpenGL/*.cpp 
        src/Platform/Window/*.cpp 
        vendor/include/imgui/*.cpp
)

# library creation
add_library(GameEngine2D 
    STATIC 
        ${SOURCES}
)
target_link_libraries(GameEngine2D  
    PUBLIC
        GLAD
        libspdlog.a
        glfw.3.dylib
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
        vendor/include        
        vendor/include/glad/include
)