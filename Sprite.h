//
// Created by jtv on 18.10.2023.
//

#pragma once

#include <iostream>
#include <memory>
#include <thread>
#include <mutex>


#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Engine{



class Sprite{
public:
    Sprite() = default;
    Sprite(std::string path);
    ~Sprite();

    void operator()(std::string path);

    Sprite(const Sprite& other);
    Sprite& operator=(const Sprite& other);

    GLuint GetRawTextureHandle();
    void BindTexture(uint32_t loc);
    void CreateTexture();

    unsigned char *data; 
private:
    std::shared_ptr<GLuint> tex;

    int x, y;


    void LoadSprite(std::string path);
    void CopyFrom(const Sprite& other);
};
}