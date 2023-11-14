//
// Created by jtv on 15.10.2023.
//

#include "Window.h"



namespace Engine{


bool Window::exists = false;
GLFWwindow* Window::window = nullptr;
const uint32_t& Window::winWidth = Window::width;
const uint32_t& Window::winHeight = Window::height;
uint32_t Window::width = 0;
uint32_t Window::height = 0;

void Window::CreateWindow(uint32_t width_, uint32_t height_, std::string title,
                            bool fullscreen, bool resizable) {
    if(exists){
        std::cerr << "Window exists already exists, make sure to destroy it first before creating another one" << std::endl;
        return;
    }

    width = width_;
    height = height_;

    if(!glfwInit()){
        std::cerr << "Failed to init GLFW" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, resizable);

    window = glfwCreateWindow(width, height, title.c_str(), fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    if(!window){
        std::cerr << "Failed to create a GLFW window" << std::endl;
        DestroyWindow();
        return;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr << "Failed to init GLAD" << std::endl;
        return;
    }

    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);

    


    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

    exists = true;
}

void Window::Clear(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Display(){
    glfwSwapBuffers(window);
}

void Window::SetClearColor(glm::vec4 color){
    glClearColor(color.x, color.y, color.z, color.w);
}

GLFWwindow* Window::GetGLFWWindow() {
    return window;
}

void Window::DestroyWindow() {
    width = 0;
    height = 0;
    exists = false;
    glfwSetWindowShouldClose(window, true);

}

void Window::FramebufferSizeCallback(GLFWwindow* window, int w, int h){
    glViewport(0, 0, w, h);
    width = w;
    height = h;
}

}
