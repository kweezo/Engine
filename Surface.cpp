//
// Created by jtv on 15.10.2023.
//

#include "Surface.h"


namespace Engine{

bool Surface::initialized = false;
GLuint Surface::VBO = 0;
GLuint Surface::EBO = 0;
Shader Surface::shader = Shader();
Shader Surface::shaderInstanced = Shader();

Surface::Surface(){
    if(!initialized){
        Initialize();
    }
}

Surface::Surface(glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation, Sprite sprite){
    if(!initialized){
        Initialize();
    }
    CreateVAO();

    this->pos = pos;
    this->scale = scale;
    this->rotation = rotation;
    this->sprite = sprite;

    isBillboard = false;

    UpdateModelMatrix();    

    useCount.reset(new bool);
}

Surface::Surface(const Surface& other){
    CopyFrom(other);
}

Surface& Surface::operator=(const Surface& other){
    if(this == &other){
        return *this;
    }

    CopyFrom(other);

    return *this;
}

void Surface::CopyFrom(const Surface& other){
    VAO = other.VAO;
    instanceVBO = other.instanceVBO;

    model = other.model;

    pos = other.pos;
    rotation = other.rotation;
    scale = other.scale;

    useCount = other.useCount;
}

Surface::~Surface(){
    if(useCount.use_count() == 1){
        glDeleteBuffers(1, &instanceVBO);
        glDeleteVertexArrays(1, &VAO);
    }
}

void Surface::CreateVAO(){
    glCreateVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);


    glEnableVertexAttribArray(0);

}

void Surface::CreateInstanceVBO(){
    glCreateBuffers(1, &instanceVBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(0 * sizeof(float)));
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(4 * sizeof(float)));
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(8 * sizeof(float)));
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(12 * sizeof(float)));

    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);

    glVertexAttribDivisor(1, 1);
    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
}

void Surface::UpdateModelMatrix(){
    model = glm::mat4(1.0f);

    model = glm::translate(model, pos);
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(1, 0, 0));
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
    model = glm::scale(model, scale);
}

void Surface::SetPosition(glm::vec3 pos){
    this->pos = pos;
    UpdateModelMatrix();
}

void Surface::SetScale(glm::vec3 scale){
    this->scale = scale;
    UpdateModelMatrix();
}

void Surface::SetRotation(glm::vec3 rotation){
    this->rotation = rotation;
    UpdateModelMatrix();
}

void Surface::ToggleBillboard(){
    isBillboard = isBillboard ? false : true;
}


void Surface::UpdateInstanceVBO(std::vector<glm::vec3>& newTransform){
    if(newTransform.size() % 3 != 0){
        std::cerr << "ABORTING. NOT UPDATING THE INSTANCE VBO, newTransform not divisible by 3" << std::endl;
        return;
    }

    instanceCount = newTransform.size()/3;

    std::vector<float> v;
    for(uint32_t i = 0; i < newTransform.size()/3; i++){
        glm::vec3 instancePos = newTransform[i*3];
        glm::vec3 instanceScale = newTransform[i*3+1];
        glm::vec3 instanceRotation = newTransform[i*3+2];
        glm::mat4 instanceModel = glm::mat4(1.0f);

        instanceModel = glm::translate(instanceModel, instancePos);
        instanceModel = glm::rotate(instanceModel, glm::radians(instanceRotation.y), glm::vec3(1, 0, 0));
        instanceModel = glm::rotate(instanceModel, glm::radians(instanceRotation.x), glm::vec3(0, 1, 0));
        instanceModel = glm::rotate(instanceModel, glm::radians(instanceRotation.z), glm::vec3(0, 0, 1));
        instanceModel = glm::scale(instanceModel, instanceScale);

        v.push_back(instanceModel[0][0]);
        v.push_back(instanceModel[1][0]);
        v.push_back(instanceModel[2][0]);
        v.push_back(instanceModel[3][0]);

        v.push_back(instanceModel[0][1]);
        v.push_back(instanceModel[1][1]);
        v.push_back(instanceModel[2][1]);
        v.push_back(instanceModel[3][1]);

        v.push_back(instanceModel[0][2]);
        v.push_back(instanceModel[1][2]);
        v.push_back(instanceModel[2][2]);
        v.push_back(instanceModel[3][2]);

        v.push_back(instanceModel[0][3]);
        v.push_back(instanceModel[1][3]);
        v.push_back(instanceModel[2][3]);
        v.push_back(instanceModel[3][3]);
    }

    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * v.size(), v.data(), GL_DYNAMIC_DRAW);

}

void Surface::Draw(){
    shader.Use();
    sprite.BindTexture(GL_TEXTURE0);


    glUniformMatrix4fv(shader.GetUniformLoc("model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniform1i(shader.GetUniformLoc("tex"), 0);
    glUniform1i(shader.GetUniformLoc("billboard"), isBillboard);
    

    Camera::ApplyViewProjectionMatrix(shader);

    //TODO implement in shader
    Light::ApplyGlobalLight(shader);

    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Surface::DrawInstanced(){
    glBindVertexArray(VAO);

    shaderInstanced.Use();
    sprite.BindTexture(GL_TEXTURE0);

    Camera::ApplyViewProjectionMatrix(shaderInstanced);

    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, instanceCount);
}

void Surface::ClearInstanceVBO(){
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);

    glBufferData(instanceVBO, 0, 0, GL_STATIC_DRAW);
}

const float vertices[] = {
    -0.5, -0.5,
    0.5, -0.5,
    -0.5, 0.5,
    0.5, 0.5
};
const unsigned int indices[] = {
    0, 1, 2,
    1, 2, 3
};
void Surface::Initialize(){
    initialized = true;    


    glCreateBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glCreateBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    shader = Shader("shaders/surface.vert", "shaders/surface.frag");
    shaderInstanced = Shader("shaders/surfaceInstanced.vert", "shaders/surface.frag");
}

}
