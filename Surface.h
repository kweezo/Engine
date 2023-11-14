//
// Created by jtv on 15.10.2023.
//

#ifndef ENGINE_SURFACE_H
#define ENGINE_SURFACE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <cmath>
#include <memory>

#include "Shader.h"
#include "Sprite.h"
#include "Camera.h"
#include "Light.h"

namespace Engine {
class Surface {
private:
    static void Initialize();
    void CreateVAO();

    static bool initialized;

    static GLuint VBO, EBO;

    static Shader shader;
    static Shader shaderInstanced;

    GLuint VAO = 0, instanceVBO;

    glm::mat4 model;
    glm::vec3 pos, rotation, scale;

    uint32_t instanceCount;

    Sprite sprite;

    std::shared_ptr<bool/*only cuz its a byte*/> useCount;
    void CopyFrom(const Surface& other);

    void UpdateModelMatrix();

    bool isBillboard;
public:
    Surface();
    Surface(glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation, Sprite sprite);

    Surface(const Surface& other);
    Surface& operator=(const Surface& other);

    ~Surface();

    //Surface(const Surface& other);

    void CreateInstanceVBO();

    void UpdateInstanceVBO(std::vector<glm::vec3>& newTransform/*each instance has scale pos and rotation*/);
    void ClearInstanceVBO();

    void SetPosition(glm::vec3 pos);
    void SetScale(glm::vec3 scale);
    void SetRotation(glm::vec3 rotation);

    void ToggleBillboard();

    void Draw();
    void DrawInstanced();

};
}

#endif //ENGINE_SURFACE_H
