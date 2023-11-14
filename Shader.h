//
// Created by jtv on 18.10.2023.
//

#pragma once

#include <iostream>
#include <fstream>
#include <memory>

#include <glad/glad.h>

namespace Engine{

class Shader{
public:
    Shader() = default;
    Shader(std::string vertexPath, std::string fragmentPath);
    ~Shader();
    Shader(const Shader& other);
    Shader& operator=(const Shader& other);

    GLuint GetUniformLoc(std::string name);
    void Use();
    GLuint GetRaw();

private:

    void CopyFrom(const Shader& other);

    std::string ReadFile(std::string path);

    std::shared_ptr<GLuint> program;
};

}
