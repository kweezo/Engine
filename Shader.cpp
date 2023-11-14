#include "Shader.h"

namespace Engine{
Shader::Shader(std::string vertexPath, std::string fragmentPath){
    std::string vertSRC = ReadFile(vertexPath);
    std::string fragSRC = ReadFile(fragmentPath);

    const char* cVertSRC = vertSRC.data();
    const char* cFragSRC = fragSRC.data();




    GLuint vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    fragment = glCreateShader(GL_FRAGMENT_SHADER);


    glShaderSource(vertex, 1, &cVertSRC, nullptr);
    glCompileShader(vertex);

    int success;

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success){
        char infoLog[512];
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cerr << "Failed to compile the vertex shader ERR: " << std::endl << infoLog;
        return;
    }


    glShaderSource(fragment, 1, &cFragSRC, nullptr);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success){
        char infoLog[512];
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cerr << "Failed to compile the fragment shader ERR: " << std::endl << infoLog;
        return;
    }

    program.reset(new GLuint);        

    program.get()[0] = glCreateProgram();


    glAttachShader(program.get()[0], vertex);
    glAttachShader(program.get()[0], fragment);

    glLinkProgram(program.get()[0]);
    
    glGetProgramiv(program.get()[0], GL_LINK_STATUS, &success);
    if(!success){
        char infoLog[512];
        glGetProgramInfoLog(program.get()[0], 512, nullptr, infoLog);
        std::cerr << "Failed to compile the fragment shader ERR: " << std::endl << infoLog;
        return;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader(){
    if(program.use_count() == 1){
        glDeleteProgram(program.get()[0]);
    }
}

Shader::Shader(const Shader& other){
    CopyFrom(other);
}

Shader& Shader::operator=(const Shader& other){
    if(this == &other){
        return *this;
    }

    CopyFrom(other);

    return *this;
}

GLuint Shader::GetUniformLoc(std::string name){
    return glGetUniformLocation(program.get()[0], name.c_str());
}

void Shader::Use(){
    glUseProgram(program.get()[0]);
}

GLuint Shader::GetRaw(){
    return program.get()[0];
}

void Shader::CopyFrom(const Shader& other){
    program = other.program;
}

std::string Shader::ReadFile(std::string path){
    std::fstream in(path);

    if(!in.is_open()){
        std::cerr << "Failed to open " << path << std::endl;
        return "";
    }

    std::string out;

    for(std::string line; getline(in, line);){
        out += line + '\n';
    }

    return out;
}



}