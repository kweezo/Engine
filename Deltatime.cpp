#include "Deltatime.h"

#include <iostream>
namespace Engine{
    float deltaTime = 0;
    float prevFrame = 0;
    void CalculateDeltaTime(){
        deltaTime = glfwGetTime() - prevFrame;
        prevFrame = glfwGetTime();
        deltaTime *= 3;

    };
}