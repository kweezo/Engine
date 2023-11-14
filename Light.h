//
// Created by jtv on 2.11.2023.
//

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

#include "Shader.h"

namespace Engine{

class Light{
public:
    static void SetGlobalLightDir(glm::vec3 orientation);
    static void SetGlobalLightColor(glm::vec3 color);
    static void SetGlobalLightBrightness(float brightness);

    static void ApplyGlobalLight(Shader shader);

    //void ApplyLight(Shader shader);

private:

    static glm::vec3 globalLightOrientation;
    static glm::vec3 globalLightColor;
    static float globalLightBrightness;
};

}