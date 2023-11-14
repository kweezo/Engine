#include "Camera.h"

namespace Engine{

const glm::vec3 UP = {0.0, 1.0, 0.0};

glm::vec3 Camera::pos = {};
glm::vec2 Camera::orientation = {};

glm::mat4 Camera::view = {};
glm::mat4 Camera::projection = {};

glm::vec3 Camera::cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

const float Camera::speed = 0.1;
const float Camera::sensitivity = 0.06;

double lastMouseX, lastMouseY;

float yaw = 30;
float pitch = 30;

void Camera::Init(){
    projection = glm::perspective(glm::radians(55.0f), (float)Window::winWidth/(float)Window::winHeight, 0.01f, 10000.0f);
    pitch = -89;
    UpdateViewMatrix();
}

void Camera::SetPos(glm::vec3 newPos){
    pos = newPos;
    UpdateViewMatrix();
}

void Camera::SetOrientation(glm::vec2 newOrientation){
    orientation = newOrientation;
    UpdateViewMatrix();
}

void Camera::ApplyViewProjectionMatrix(Shader& shader){
    shader.Use();
    glUniformMatrix4fv(shader.GetUniformLoc("projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(shader.GetUniformLoc("view"), 1, GL_FALSE, glm::value_ptr(view));
}

void Camera::UpdateViewMatrix(){
    view = glm::lookAt(pos, pos + cameraFront, UP);
}

glm::vec3 Camera::GetPos(){
    return pos;
}


void Camera::BasicController(){
    int xDir = glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_D) - glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_A);
    int zDir = glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_W) - glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_S);

    pos += glm::normalize(glm::cross(cameraFront, UP)) * (float)speed * (float)xDir;
    pos += zDir * speed * cameraFront;

    double mouseX, mouseY;
    glfwGetCursorPos(Window::GetGLFWWindow(), &mouseX, &mouseY);

    double xOffset = mouseX-lastMouseX;
    double yOffset = mouseY-lastMouseY;

    lastMouseX = mouseX;
    lastMouseY = mouseY;

    xOffset *= sensitivity;
    yOffset *= sensitivity;

    yaw += xOffset;
    pitch -= yOffset;

    pitch = std::clamp(pitch, -89.0f, 89.0f);

    cameraFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront.y = sin(glm::radians(pitch));
    cameraFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    cameraFront = glm::normalize(cameraFront);



    UpdateViewMatrix();
}
};
