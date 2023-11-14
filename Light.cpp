
//
// Created by jtv on 3.11.2023.
//

#include "Light.h"

namespace Engine{

glm::vec3 Light::globalLightOrientation = glm::vec3(1.0f);
glm::vec3 Light::globalLightColor = glm::vec3(1.0f);
float Light::globalLightBrightness = 1.0f;

void Light::SetGlobalLightDir(glm::vec3 orientation){
    globalLightOrientation = orientation;    
}

void Light::SetGlobalLightColor(glm::vec3 color){
   globalLightColor = color; 
}

void Light::SetGlobalLightBrightness(float brightness){
    globalLightBrightness = brightness;
}

void Light::ApplyGlobalLight(Shader shader){
    glUniform3fv(shader.GetUniformLoc("globalLightOrientation"), 1, glm::value_ptr(globalLightOrientation));
    glUniform3fv(shader.GetUniformLoc("globalLightColor"), 1, glm::value_ptr(globalLightColor));
    glUniform1f(shader.GetUniformLoc("globalLightBrightness"), globalLightBrightness);
}

}