#pragma once

#include <algorithm>
#include <vector>
#include <iostream>
#include <limits>
#include <stdlib.h>
#include <array>
#include <algorithm>
#include <math.h>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Deltatime.h"

namespace Engine{

#define PI 3.141593f


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

    //TODO dont recalculate axes each collision check I guess
class Body{
public:
    Body() = default;
    Body(glm::vec3 pos, glm::vec3 size, float mass, bool isStatic);

    void RemoveFromSimulation();
    void ReaddToSimulation();

    void DrawCollider();

    void CheckCollision(Body* other);

    void ApplyImpulse(glm::vec3 impulse);
    void SetVel(glm::vec3 newVel); //WARNING not recommended to use unless necessary

    std::array<glm::vec3, 3> GetAxes();

    void Update();


    bool IsGrounded();
    bool IsStatic();

    glm::vec3 GetPos();
    void SetPos(glm::vec3 newPos);

    glm::vec3 GetSize();
    void SetSize(glm::vec3 newSize);

    glm::vec3 GetOrientation();
    void SetOrientation(glm::vec3 newOrientation);

    float GetMass();
    void SetMass(float newMass);

    glm::vec3 vertices[COLLIDER_VERTEX_COUNT];
private:

    bool isStatic;
    bool isGrounded;

    glm::vec3 pos;
    glm::vec3 vel;
    glm::vec3 size;
    glm::vec3 orientation;
    float mass;
    float density;

    std::array<glm::vec3, 3> axes;
    void CalculateAxes();

    glm::vec3 points[COLLIDER_VERTEX_COUNT];

    void CopyFrom(const Body& other);
    void UpdateVertices();

    glm::mat4 model;

    static OverlapInfo CheckOverlap(Body* b1, Body* b2, glm::vec3 axis);
    static float CalculateOverlap(float aMinProj, float aMaxProj, float bMinProj, float bMaxProj);

    void ApplyGravity();

    static std::vector<Body*> bodies;

};
};