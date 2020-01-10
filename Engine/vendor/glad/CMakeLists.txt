project(GLAD)

include_directories(include)
add_library(GLAD src/glad.c)
target_include_directories(GLAD 
    PUBLIC 
        include
)