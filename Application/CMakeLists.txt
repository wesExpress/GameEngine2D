project (Application)

add_executable(Application src/Application.cpp)
target_link_libraries(Application 
    PRIVATE 
        GameEngine2D
)