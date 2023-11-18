#include <iostream>

#include "Engine.h"


class Manager{ 
public:
    void Init();
    void Update();
    void ShutDown();

    Engine::Window window;
    Engine::Model model;
    Engine::Model model1;
    Engine::Model model2;
    Engine::Model model3;
    Engine::Model model4;
    Engine::Body body;
    Engine::Body body2;
    Engine::Body body3;
};

void Manager::Init(){
    Engine::Window::CreateWindow(1920, 1080, "LE WINDOW", false, true);

    Engine::Camera::Init();


//     model = Engine::Model("res/rat.fbx", glm::vec3(0), glm::vec3(100), glm::vec3(0.0f, 0.0f, 0.0f));

    Engine::Window::SetClearColor({0.5, 0.5, 0.5, 1.0});

    Engine::Light::SetGlobalLightColor(glm::vec3(1.0f, 1.0f, 1.0f));
    Engine::Light::SetGlobalLightBrightness(1.f);

    body = Engine::Body(glm::vec3(0), glm::vec3(1, 2.5, 1), 0.2, false);
    body2 = Engine::Body(glm::vec3(0, -20, 0), glm::vec3(5, 0.1, 5), 600, true);
    body3 = Engine::Body(glm::vec3(3, -20, 3), glm::vec3(1, 5, 1), 600, true);
    model2 = Engine::Model("res/cube.obj", glm::vec3(3, -20, 3), glm::vec3(1, 5, 1), glm::vec3(0));
    model3 = Engine::Model("res/cube.obj", glm::vec3(0, -20, 0), glm::vec3(5, 0.1, 5), glm::vec3(0));
    model4 = Engine::Model("res/cube.obj", glm::vec3(0), glm::vec3(1, 2.5, 1), glm::vec3(0));

}

void Manager::Update(){
    Engine::Window::Clear();


    body.CheckCollision(&body2);
    body.CheckCollision(&body3);
    body.Update();

    model4.SetPosition(body.pos);
    model.SetPosition(body.pos);

    model2.Draw();
    model3.Draw();
//    model.Draw();
    model4.Draw();


    if(glfwGetKey(Engine::Window::GetGLFWWindow(), GLFW_KEY_UP)){
        body.vel = glm::vec3(0, 0, 1);
    } 
    if(glfwGetKey(Engine::Window::GetGLFWWindow(), GLFW_KEY_DOWN)){
        body.vel = glm::vec3(0, 0, -1);
    }
    if(glfwGetKey(Engine::Window::GetGLFWWindow(), GLFW_KEY_LEFT)){
        body.vel = glm::vec3(-1, 0, 0);
    }
    if(glfwGetKey(Engine::Window::GetGLFWWindow(), GLFW_KEY_RIGHT)){
        body.vel = glm::vec3(1, 0, 0);
    }

//    model.SetRotation(glm::vec3(0, -90, glfwGetTime()*50));


    Engine::Camera::BasicController();

    Engine::Window::Display();
}

void Manager::ShutDown(){
    Engine::Window::DestroyWindow();
}

int main() {
    Manager manager;

    Engine::Start(&manager);

    return 0;
}

//todo for tmrw. start making the game and make sure rp3d rotations and the opengl ones work nicely