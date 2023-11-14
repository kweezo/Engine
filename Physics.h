#pragma once

#include <algorithm>
#include <vector>
#include <iostream>

#include <glm/glm.hpp>

#include "Deltatime.h"

namespace Engine{

#define GRAVITY -9.81f
#define DRAG_COEFFICIENT 0.1f /*(i made it ui made it up)*/
#define AIR_DENSITY 1.2
#define DEFAULT_ELASTICITY 0.3f
#define DEFAULT_FRICTION 0.2f

#define COLLISION_POINT_SPACING 5.0f
#define MAX_COLLISION_POINT_DIST 2.0f
#define COLLISION_POINT_SAFE_SPACE 0.05f


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
private:

    std::vector<glm::vec3> xSideCollisionPoints;
    std::vector<glm::vec3> ySideCollisionPoints;
    std::vector<glm::vec3> zSideCollisionPoints;

    void CalculateCollisionPoints();

    static bool IsRayIntersecting(Body* other, glm::vec3 p1, glm::vec3 p2, float numIcrements);

    void ApplyGravity();
    void RecalculateTerminalVelocity();

    float terminalV;

    static std::vector<Body*> bodies;

};
};