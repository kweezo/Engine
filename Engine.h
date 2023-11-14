#pragma once

#include "Light.h"
#include "Shader.h"
#include "Sprite.h"
#include "Surface.h"
#include "Window.h"
#include "Model.h"
#include "Deltatime.h"
#include "Physics.h"

namespace Engine{


template<typename T>
void Start(T *manager){

    manager->Init();

    deltaTime = glfwGetTime();
    prevFrame = glfwGetTime();

    while(!glfwWindowShouldClose(Window::GetGLFWWindow())){
        CalculateDeltaTime();

        glfwPollEvents();
        manager->Update();
    }
    manager->ShutDown();
}
}