//
// Created by jtv on 21.10.2023.
//

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <functional>
#include <memory>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Sprite.h"
#include "Shader.h"
#include "Camera.h"
#include "Light.h"

namespace Engine{



struct Mesh{
    GLuint VAO, VBO, uvVBO, normalVBO,  EBO;

    uint32_t baseColorSpriteIndex, normalSpriteIndex;
    uint32_t indiceCount;

    glm::vec3 baseColorModifier;

    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> texCoords;
    std::vector<GLuint> indices;
};

class Model{
public:
    Model();
    Model(std::string modelPath, glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation);

    void SetPosition(glm::vec3 pos);
    void SetScale(glm::vec3 scale);
    void SetRotation(glm::vec3 rotation);

    void Draw();

private:
    void UpdateModelMatrix();

    void LoadModel(std::string path);
    void ProcessNode(aiNode* node, const aiScene* scene, std::string dir);

    void CreateBuffers();

    std::shared_ptr<char> useCount;

    void CopyFrom(const Model& other);

    std::vector<Mesh*> meshes; 

    std::vector<Sprite*> sprites;
    std::unordered_map<std::string, int> spriteMap;//path of sprite and its index in sprites vector

    std::vector<std::thread> threads;

    glm::vec3 pos, rotation, scale;
    glm::mat4 model;

    static bool initialized;
    static Shader shader;


};

}