project (Application)

add_executable(Application src/Application.cpp src/TestLayer.cpp src/Sandbox2D.cpp)
target_link_libraries(Application 
    PRIVATE 
        Engine
)