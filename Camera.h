
//
// Created by jtv on 20.10.2023.
//

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <algorithm>

#include "Shader.h"
#include "Window.h"

namespace Engine{
class Camera{ //abusing classes instead of just using namespaces, the sequel
public:
    static void Init();
    static void SetPos(glm::vec3 newPos);
    static void SetOrientation(glm::vec2 newOrientation); 

    static glm::vec3 GetPos();

    static void ApplyViewProjectionMatrix(Shader& shader);

    static void BasicController(/*float deltatime ill get to it when ill get to it*/);
private:
    static glm::vec3 pos;
    static glm::vec2 orientation;

    static glm::mat4 view, projection;

    static glm::vec3 cameraFront;

    static const float speed;
    static const float sensitivity;

    static void UpdateViewMatrix();
};
}