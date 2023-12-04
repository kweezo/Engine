#include "Deltatime.h"

#include <iostream>
namespace Engine{

#define MAX_DELTATIME 0.1f // 10fps

    float deltaTime = 0;
    float prevFrame = 0;
    void CalculateDeltaTime(){
        deltaTime = (glfwGetTime() - prevFrame) / 1000;
        prevFrame = glfwGetTime();

        if(deltaTime > MAX_DELTATIME){
            deltaTime = MAX_DELTATIME;
        }

        deltaTime *= 2000;
    };
}