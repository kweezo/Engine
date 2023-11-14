//
// Created by jtv on 15.10.2023.
//

#ifndef ENGINE_WINDOW_H
#define ENGINE_WINDOW_H

#include <iostream>
#include <cstdint>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

namespace Engine {


class Window {
public:
    static void CreateWindow(uint32_t width, uint32_t height, std::string title, bool fullscreen, bool resizable);
    static void DestroyWindow();

    static void Clear();
    static void Display();

    static void SetClearColor(glm::vec4 color);

    static GLFWwindow* GetGLFWWindow();

    static const uint32_t &winWidth;
    static const uint32_t &winHeight;

    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
private:
    static bool exists;
    static GLFWwindow* window;

    static uint32_t width, height;
}; //ABUSING CLASSES INSTEAD OF JUST USING NAMESPACES LIKE A BOSS😎
}

#endif //ENGINE_WINDOW_H
