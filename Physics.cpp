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
    model = glm::scale(model, size);

    for(uint32_t i = 0; i < SHAPE_POINTS; i++){
        glm::vec4 v = model*glm::vec4(points[i], 1.0f);
        vertices[i] = glm::vec3(v.x, v.y, v.z) / v.w;
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

void Body::CheckCollision(Body* other){

    if(isStatic && other->isStatic){
        return;
    }

    bool intersection = true;

    for(uint32_t i = 0; i < SHAPE_POINTS; i++){

        glm::vec3 curr = vertices[i];
        glm::vec3 next = vertices[(i + 1) % SHAPE_POINTS];
        glm::vec3 third = vertices[(i + 2) % SHAPE_POINTS];
        glm::vec3 edges[2];

        edges[0] = next - curr;
        edges[1] = third - curr;

        glm::vec3 axis = glm::cross(edges[0], edges[1]);

        float aMaxProj = -std::numeric_limits<float>::infinity();
        float aMinProj = std::numeric_limits<float>::infinity();

        float bMaxProj = -std::numeric_limits<float>::infinity();
        float bMinProj = std::numeric_limits<float>::infinity();
        
    
        for(glm::vec3 p : vertices){
            float proj = glm::dot(axis, p);

            if(proj < aMinProj){
                aMinProj = proj;
            }
            if(proj > aMaxProj){
                aMaxProj = proj;
            }
        }

        for(glm::vec3 p : other->vertices){
            float proj = glm::dot(axis, p);

            if(proj < bMinProj){
                bMinProj = proj;
            }
            if(proj > bMaxProj){
                bMaxProj = proj;
            }
        }

        //std::cout << aMinProj << " " << aMaxProj << " " << bMinProj << " " << bMaxProj << std::endl;

        if(aMaxProj < bMinProj || aMinProj > bMaxProj){
            intersection = false;
        }
    }

    if(!intersection){
        return;
    }

    vel.y = 0;
    pos.y -= GRAVITY;
}

void Body::ApplyImpulse(glm::vec3 impulse){
    vel += impulse;
}


bool Body::IsRayIntersecting(Body* other, glm::vec3 p1, glm::vec3 p2, float numIncrements){
    glm::vec3 dir = p2 - p1;
    glm::vec3 incr = glm::abs(dir / numIncrements);
    dir = glm::normalize(dir);

    glm::vec3 p = p2;

    for(uint32_t i = 0; i < numIncrements; i++){
        p = p2 - incr * dir * (float)i;
        if(p.x > other->pos.x - other->size.x && p.x < other->pos.x + other->size.x
        && p.y > other->pos.y - other->size.y && p.y < other->pos.y + other->size.y
        && p.z > other->pos.z - other->size.z && p.z < other->pos.z + other->size.z){
            return true;
        }
    }
    
    return false;    
}


}