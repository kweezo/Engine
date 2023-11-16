#pragma once

#include <algorithm>
#include <vector>
#include <iostream>
#include <limits>
#include <stdlib.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Deltatime.h"

namespace Engine{

#define GRAVITY -9.81f
#define DRAG_COEFFICIENT 0.1f /*(i made it ui made it up)*/
#define AIR_DENSITY 1.2
#define DEFAULT_ELASTICITY 0.3f
#define DEFAULT_FRICTION 0.2f

#define COLLIDER_VERTEX_COUNT 8

struct OverlapInfo{
    bool isOverlapping;
    float overlap;
};

class Body{
public:
    Body() = default;
    Body(glm::vec3 pos, glm::vec3 size, float mass, bool isStatic);
    void CheckCollision(Body* other);

    void ApplyImpulse(glm::vec3 impulse);

    void Update();
    glm::vec3 pos;
    glm::vec3 vel;
    glm::vec3 size;
    float mass;

    bool isStatic;
    bool isGrounded;

    float density;
    glm::vec3 points[COLLIDER_VERTEX_COUNT];
    glm::vec3 vertices[COLLIDER_VERTEX_COUNT];
private:

    void UpdateVertices();

    glm::mat4 model;


    static OverlapInfo CheckOverlap(Body* b1, Body* b2, glm::vec3 axis);
    static float CalculateOverlap(float aMinProj, float aMaxProj, float bMinProj, float bMaxProj);

    void ApplyGravity();
    void RecalculateTerminalVelocity();

    float terminalV;

    static std::vector<Body*> bodies;

};
};