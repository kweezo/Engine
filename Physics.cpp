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

    RecalculateTerminalVelocity();
    CalculateCollisionPoints();
}

void Body::CalculateCollisionPoints(){
    glm::vec2 xPDist;
    xPDist.x = std::clamp(size.z/COLLISION_POINT_SPACING, 0.0f, MAX_COLLISION_POINT_DIST*0.5f); // just do times 2
    xPDist.y = std::clamp(size.y/COLLISION_POINT_SPACING, 0.0f, MAX_COLLISION_POINT_DIST*0.5f);

    glm::vec2 yPDist;
    yPDist.x = std::clamp(size.x/COLLISION_POINT_SPACING, 0.0f, MAX_COLLISION_POINT_DIST*0.5f);
    yPDist.y = std::clamp(size.z/COLLISION_POINT_SPACING, 0.0f, MAX_COLLISION_POINT_DIST*0.5f);
    
    glm::vec2 zPDist;
    zPDist.x = std::clamp(size.x/COLLISION_POINT_SPACING, 0.0f, MAX_COLLISION_POINT_DIST*0.5f);
    zPDist.y = std::clamp(size.y/COLLISION_POINT_SPACING, 0.0f, MAX_COLLISION_POINT_DIST*0.5f);
    
   glm::vec3 p; 
   for(float y = -size.y + COLLISION_POINT_SAFE_SPACE; y < size.y - COLLISION_POINT_SAFE_SPACE; 
   y = std::clamp(y + xPDist.y*2, -size.y + COLLISION_POINT_SAFE_SPACE, size.y - COLLISION_POINT_SAFE_SPACE)){
       for(float x = -size.z + COLLISION_POINT_SAFE_SPACE; x < size.z - COLLISION_POINT_SAFE_SPACE;
        x = std::clamp(x + xPDist.x*2, -size.z + COLLISION_POINT_SAFE_SPACE, size.z - COLLISION_POINT_SAFE_SPACE)){
            p = glm::vec3(size.x, y, x); //DONT FORGET TO OFFSET BY POS
            xSideCollisionPoints.push_back(p);
        }
   }

   for(float y = -size.z + COLLISION_POINT_SAFE_SPACE; y < size.z - COLLISION_POINT_SAFE_SPACE; 
   y = std::clamp(y + yPDist.y*2, -size.z + COLLISION_POINT_SAFE_SPACE, size.z - COLLISION_POINT_SAFE_SPACE)){
       for(float x = -size.x + COLLISION_POINT_SAFE_SPACE; x < size.x - COLLISION_POINT_SAFE_SPACE; 
       x = std::clamp(x + yPDist.x*2, -size.x + COLLISION_POINT_SAFE_SPACE, size.x - COLLISION_POINT_SAFE_SPACE)){
            p = glm::vec3(y, size.y, x); 
            ySideCollisionPoints.push_back(p);
        }
   }

   for(float y = -size.y + COLLISION_POINT_SAFE_SPACE; y < size.y - COLLISION_POINT_SAFE_SPACE;
    y = std::clamp(y + zPDist.y*2, -size.y + COLLISION_POINT_SAFE_SPACE, size.y - COLLISION_POINT_SAFE_SPACE)){
       for(float x = -size.x + COLLISION_POINT_SAFE_SPACE; x < size.x - COLLISION_POINT_SAFE_SPACE; 
       x = std::clamp(x + zPDist.x*2, -size.x + COLLISION_POINT_SAFE_SPACE, size.x - COLLISION_POINT_SAFE_SPACE)){
            p = glm::vec3(x, y, size.z); 
            zSideCollisionPoints.push_back(p);
        }
   }
   
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

void Body::Update(){
    if(isStatic){
        return;
    }

    ApplyGravity();
    pos += vel * deltaTime;


    //do it in a global func or smthn
    isGrounded = false;
}

void Body::CheckCollision(Body* other){

    if(isStatic && other->isStatic){
        return;
    }

    float greatestAxis1, greatestAxis2;

    if(size.x > size.y && size.x > size.z){
        greatestAxis1 = size.x;
    }
    else if(size.y > size.z){
        greatestAxis1 = size.y;
    }
    else{
        greatestAxis1 = size.z;
    }

    if(other->size.x > other->size.y && other->size.x > other->size.z){
        greatestAxis2 = other->size.x;
    }
    else if(other->size.y > other->size.z){
        greatestAxis2 = other->size.y;
    }
    else{
        greatestAxis2 = other->size.z;
    }

    //rough calculation to see if it's even worth checking
    if(!(sqrt(pow(pos.x - other->pos.x, 2) + pow(pos.y - other->pos.y, 2) + pow(pos.z - other->pos.z, 2)) < greatestAxis1 + greatestAxis2)){
        return;
    }

    //spread out evenly 5 times with max 0f 0.5 spacing top middle and bottom also max of 0.5 times??

    //todo check in increments of 0.5
    glm::vec3 dir = glm::vec3(0);

    if(!dir.length()){
        for(glm::vec3 p : ySideCollisionPoints){
            if(IsRayIntersecting(other, pos, p + pos, 2)){
                dir = glm::vec3(0, -1, 0);
                isGrounded = true;
                if(vel.y < 0){
                    vel.y = 0;
                }
                break;
            }
        }
    }
    else if(!dir.length()){

    for(glm::vec3 p : xSideCollisionPoints){
        if(IsRayIntersecting(other, pos, p + pos, 2)){
            dir = glm::vec3(-1, 0, 0);
            break;
        }
    }
    }
    if(!dir.length()){
        for(glm::vec3 p : xSideCollisionPoints){
            if(IsRayIntersecting(other, pos, glm::vec3(-p.x, p.y, p.z) + pos, 2)){
                dir = glm::vec3(1, 0, 0);
                break;
            }
        }
    }
    else if(!dir.length()){
        for(glm::vec3 p : zSideCollisionPoints){
            if(IsRayIntersecting(other, pos, p + pos, 2)){
                dir = glm::vec3(0, 0, -1);
                break;
            }
        }
    }
    else if(!dir.length()){
        for(glm::vec3 p : zSideCollisionPoints){
            if(IsRayIntersecting(other, pos, glm::vec3(p.x, p.y, -p.z) + pos, 2)){
                dir = glm::vec3(0, 0, 1);
                break;
            }
        }
    }
    else{
        for(glm::vec3 p : ySideCollisionPoints){
            if(IsRayIntersecting(other, pos, glm::vec3(p.x, p.y, -p.z) + pos, 2)){
                dir = glm::vec3(0, 1, 0);
                break;
            }
        }
    }

    if(dir.length() != 0){
        glm::vec3 offset;

        offset = glm::abs(glm::abs(pos - other->pos) - size - other->size) - 0.01f/*dunno why dis is needed but it is*/;

        pos += dir * offset; // pos = smthn????
    }

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