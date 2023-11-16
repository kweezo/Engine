#include "Physics.h"

namespace Engine{

Body::Body(glm::vec3 pos, glm::vec3 size, float mass, bool isStatic){
    this->pos = pos;
    this->mass = mass;
    this->size = size;
    this->isStatic = isStatic;
    this->vel = glm::vec3(0);

    float density = (size.x * size.y * size.z) / mass;

    isGrounded = false;

    points[0] = glm::vec3(-0.5f, -0.5f, -0.5f);
    points[1] = glm::vec3(-0.5f, -0.5f, 0.5f);
    points[2] = glm::vec3(-0.5f, 0.5f, -0.5f);
    points[3] = glm::vec3(-0.5f, 0.5f, 0.5f);
    points[4] = glm::vec3(0.5f, -0.5f, -0.5f);
    points[5] = glm::vec3(0.5f, -0.5f, 0.5f);
    points[6] = glm::vec3(0.5f, 0.5f, -0.5f);
    points[7] = glm::vec3(0.5f, 0.5f, 0.5f);

    UpdateVertices();


    model = glm::mat4(1.0f);

    RecalculateTerminalVelocity();
}

void Body::RecalculateTerminalVelocity(){
    terminalV = -sqrt((2 * mass * GRAVITY*-1) / (DRAG_COEFFICIENT * AIR_DENSITY * size.x * size.y)); 
}

void Body::ApplyGravity(){
    if(isGrounded){
        return;
    }
    vel.y += GRAVITY * deltaTime;


    if(vel.y < terminalV){
        vel.y = terminalV;
    }

}

void Body::UpdateVertices(){
    model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    model = glm::scale(model, size * 2.0f);

    for(uint32_t i = 0; i < COLLIDER_VERTEX_COUNT; i++){
        glm::vec4 v = model*glm::vec4(points[i], 1.0f);
        vertices[i] = glm::vec3(v.x, v.y, v.z);
    }
}

void Body::Update(){
    if(isStatic){
        return;
    }

    ApplyGravity();
    pos += vel * deltaTime;

    UpdateVertices();


    //do it in a global func or smthn
    isGrounded = false;
}
float Body::CalculateOverlap(float aMinProj, float aMaxProj, float bMinProj, float bMaxProj){
    return (aMinProj > bMinProj) ? aMinProj : bMinProj - (aMaxProj > bMaxProj) ? bMaxProj : aMaxProj; 
}

void Body::CheckCollision(Body* other){

    if(isStatic && other->isStatic){
        return;
    }

    glm::vec3 axis;


    glm::vec3 mtvAxis;
    float overlap = std::numeric_limits<float>::infinity();

    for(uint32_t i = 0; i < COLLIDER_VERTEX_COUNT; i++){
        glm::vec3 curr = vertices[i];
        glm::vec3 edges[2];

        edges[0] = vertices[(i + 1) % COLLIDER_VERTEX_COUNT]- curr;
        edges[1] = vertices[(i + 2) % COLLIDER_VERTEX_COUNT]- curr;

        axis = glm::normalize(glm::cross(edges[1], edges[0]));

        OverlapInfo overlapInfo = CheckOverlap(this, other, axis);
        if(!overlapInfo.isOverlapping){
            return;
        }

        curr = other->vertices[i];
        edges[0] = other->vertices[(i + 1) % COLLIDER_VERTEX_COUNT]- curr;
        edges[1] = other->vertices[(i + 2) % COLLIDER_VERTEX_COUNT]- curr;

        axis = glm::normalize(glm::cross(edges[1], edges[0]));

        overlapInfo = CheckOverlap(this, other, axis);
        if(!overlapInfo.isOverlapping){
            return;
        }

        axis = glm::normalize(glm::cross(vertices[(i + 1) % COLLIDER_VERTEX_COUNT] - curr,
        other->vertices[(i + 1) % COLLIDER_VERTEX_COUNT] - other->vertices[i]));

        overlapInfo = CheckOverlap(this, other, axis);
        if(!overlapInfo.isOverlapping){
            return;
        }

        axis = glm::normalize(glm::cross(vertices[(i + 2) % COLLIDER_VERTEX_COUNT] - curr,
        other->vertices[(i + 2) % COLLIDER_VERTEX_COUNT] - other->vertices[i]));
        
        overlapInfo = CheckOverlap(this, other, axis);
        if(!overlapInfo.isOverlapping){
            return;
        }

        if(overlapInfo.overlap < overlap){
            overlap = overlapInfo.overlap;
            mtvAxis = axis;
        }
    }

    
    vel = glm::vec3(0);
    
}

OverlapInfo Body::CheckOverlap(Body* b1, Body* b2, glm::vec3 axis){


    OverlapInfo overlapInfo;

    float aMaxProj = -std::numeric_limits<float>::infinity();
    float aMinProj = std::numeric_limits<float>::infinity();

    float bMaxProj = -std::numeric_limits<float>::infinity();
    float bMinProj = std::numeric_limits<float>::infinity();
    

    for(glm::vec3 p : b1->vertices){
        float proj = glm::dot(axis, p);

        if(proj < aMinProj){
            aMinProj = proj;
        }
        if(proj > aMaxProj){
            aMaxProj = proj;
        }
    }

    for(glm::vec3 p : b2->vertices){
        float proj = glm::dot(axis, p);

        if(proj < bMinProj){
            bMinProj = proj;
        }
        if(proj > bMaxProj){
            bMaxProj = proj;
        }
    }
    if(aMaxProj < bMinProj || bMaxProj < aMinProj){
        overlapInfo.isOverlapping = false;
        overlapInfo.overlap = std::numeric_limits<float>::infinity();
        return overlapInfo;
    }

    overlapInfo.isOverlapping = true;
    overlapInfo.overlap = CalculateOverlap(aMinProj, aMaxProj, bMinProj, bMaxProj);
    return overlapInfo;
}


void Body::ApplyImpulse(glm::vec3 impulse){
    vel += impulse;
}
}