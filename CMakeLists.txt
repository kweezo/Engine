cmake_minimum_required(VERSION 3.22.1)
project(Engine)

set(CMAKE_CXX_STANDARD 23)

add_compile_options(-g)

add_executable(Engine main.cpp
        Window.cpp
        Window.h
        Surface.cpp
        Surface.h
        Shader.h
        Shader.cpp
        Sprite.h
        Sprite.cpp
        Camera.h
        Camera.cpp
        Model.h
        Model.cpp
        Light.h
        Light.cpp
        Engine.h
        Engine.cpp
        Deltatime.h
        Deltatime.cpp
        Physics.h
        Physics.cpp)
        

target_link_libraries(Engine PUBLIC glfw)
target_link_libraries(Engine PUBLIC glad)
target_link_libraries(Engine PUBLIC reactphysics3d)
target_link_libraries(Engine PUBLIC assimp)




