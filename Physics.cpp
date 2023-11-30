#include "Physics.h"

namespace Engine{

Body::Body(glm::vec3 pos, glm::vec3 size, float mass, bool isStatic){
    this->pos = pos;
    this->mass = mass;
    this->size = size;
    this->isStatic = isStatic;
    this->vel = glm::vec3(0);

    float density = mass / (size.x * size.y * size.z);

    isGrounded = false;

    points[0] = glm::vec3(-0.5, -0.5, -0.5);
    points[1] = glm::vec3( 0.5, -0.5, -0.5);
    points[2] = glm::vec3( 0.5,  0.5, -0.5);
    points[3] = glm::vec3(-0.5,  0.5, -0.5);
    
    points[4] = glm::vec3(-0.5, -0.5,  0.5);
    points[5] = glm::vec3( 0.5, -0.5,  0.5);
    points[6] = glm::vec3( 0.5,  0.5,  0.5);
    points[7] = glm::vec3(-0.5,  0.5,  0.5);

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
    return std::min(bMaxProj, aMaxProj) - std::max(aMinProj, bMinProj); 
}

std::array<glm::vec3, 3> Body::CalculateAxes(){
    std::array<glm::vec3, 3> axes;

    glm::vec3 edge1 = glm::normalize(vertices[1] - vertices[0]);     
    glm::vec3 edge2 = glm::normalize(vertices[4] - vertices[0]);     
    glm::vec3 edge3 = glm::normalize(vertices[3] - vertices[0]);     


    axes[0] = edge1;
    axes[1] = edge2;
    axes[2] = edge3;


    return axes;
}

void Body::CheckCollision(Body* other){

    if(isStatic && other->isStatic){
        return;
    }

    glm::vec3 axis;

    //calculate the fucking normal axis:

    glm::vec3 mtvAxis;

    std::array<glm::vec3, 3> axes = CalculateAxes();
    std::array<glm::vec3, 3> otherAxes = other->CalculateAxes();

    float overlap = std::numeric_limits<float>::infinity();

    for(uint32_t i = 0; i < 3; i++){

        OverlapInfo overlapInfo = CheckOverlap(this, other, axes[i]);
        if(!overlapInfo.isOverlapping){
            return;
        }
        if(overlapInfo.overlap < overlap){
            overlap = overlapInfo.overlap;
            mtvAxis = axes[i];
        }

        overlapInfo = CheckOverlap(this, other, otherAxes[i]);
        if(!overlapInfo.isOverlapping){
            return;
        }
        if(overlapInfo.overlap < overlap){
            overlap = overlapInfo.overlap;
            mtvAxis = axes[i];
        }


        for(uint32_t j = 0; j < 3; j++){
            
            if(axes[i] == otherAxes[j]){
                overlapInfo = CheckOverlap(this, other, axes[i]);
                if(!overlapInfo.isOverlapping){
                    return;
                }
                if(overlapInfo.overlap < overlap){
                    overlap = overlapInfo.overlap;
                    mtvAxis = axes[i];
                }
                continue;
            }

            overlapInfo = CheckOverlap(this, other, glm::normalize(glm::cross(axes[i], otherAxes[j])));
            if(!overlapInfo.isOverlapping){
                return;
            }
            if(overlapInfo.overlap < overlap){
                overlap = overlapInfo.overlap;
                mtvAxis = glm::normalize(glm::cross(axes[i], otherAxes[j]));
            }
        }
    }
 for(uint32_t i = 0; i < 3; i++){

        OverlapInfo overlapInfo = CheckOverlap(this, other, -axes[i]);
        if(!overlapInfo.isOverlapping){
            return;
        }
        if(overlapInfo.overlap < overlap){
            overlap = overlapInfo.overlap;
            mtvAxis = -axes[i];
        }

        overlapInfo = CheckOverlap(this, other, -otherAxes[i]);
        if(!overlapInfo.isOverlapping){
            return;
        }
        if(overlapInfo.overlap < overlap){
            overlap = overlapInfo.overlap;
            mtvAxis = -axes[i];
        }


        for(uint32_t j = 0; j < 3; j++){
            
            if(axes[i] == otherAxes[j]){
                overlapInfo = CheckOverlap(this, other, -axes[i]);
                if(!overlapInfo.isOverlapping){
                    return;
                }
                if(overlapInfo.overlap < overlap){
                    overlap = overlapInfo.overlap;
                    mtvAxis = -axes[i];
                }
                continue;
            }

            overlapInfo = CheckOverlap(this, other, glm::normalize(glm::cross(-axes[i], -otherAxes[j])));
            if(!overlapInfo.isOverlapping){
                return;
            }
            if(overlapInfo.overlap < overlap){
                overlap = overlapInfo.overlap;
                mtvAxis = glm::normalize(glm::cross(-axes[i], -otherAxes[j]));
            }
        }
    }
//    std::cout << mtvAxis.x << " " << mtvAxis.y << " " << mtvAxis.z << " 1" << std::endl;

    mtvAxis.x = static_cast<float>(static_cast<int>(mtvAxis.x * 10)) / 10; //fix some float inprecisions
    mtvAxis.y = static_cast<float>(static_cast<int>(mtvAxis.y * 10)) / 10;
    mtvAxis.z = static_cast<float>(static_cast<int>(mtvAxis.z * 10)) / 10;

//    mtvAxis = glm::normalize(mtvAxis);




    pos -= mtvAxis * overlap;

    vel.y = 0;
    
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
//    std:: << std::max(aMinProj, bMinProj) - std::min(bMaxProj, aMaxProj) << std::endl;
 //   std:: << aMinProj << " " << aMaxProj << " " << bMinProj << " " << bMaxProj << std::endl;
    return overlapInfo;
}


void Body::ApplyImpulse(glm::vec3 impulse){
    vel += impulse;
}
}
//wana kms https://gamedev.stackexchange.com/questions/44500/how-many-and-which-axes-to-use-for-3d-obb-collision-with-sat