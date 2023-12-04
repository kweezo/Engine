#include "Physics.h"

namespace Engine{


std::vector<Body*> Body::bodies = {};

Body::Body(glm::vec3 pos, glm::vec3 size, float mass, bool isStatic){
    this->pos = pos;
    this->mass = mass;
    this->size = size;
    this->isStatic = isStatic;
    this->vel = glm::vec3(0);

    orientation = glm::vec3(0);

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
    CalculateAxes();


    model = glm::mat4(1.0f);

}


void Body::ApplyGravity(){
    if(isGrounded){
        return;
    }
    vel.y += GRAVITY * deltaTime;


    if(vel.y < GRAVITY){
        vel.y = GRAVITY;
    }

}

void Body::UpdateVertices(){
    model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    model = glm::scale(model, size * 2.0f);

    model = glm::rotate(model, orientation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, orientation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, orientation.z, glm::vec3(0.0f, 0.0f, 1.0f));

    for(uint32_t i = 0; i < COLLIDER_VERTEX_COUNT; i++){
        glm::vec4 v = model*glm::vec4(points[i], 1.0f);
        vertices[i] = glm::vec3(v.x, v.y, v.z);
    }

    CalculateAxes();
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

void Body::CalculateAxes(){
    glm::vec3 edge1 = glm::normalize(vertices[1] - vertices[0]);     
    glm::vec3 edge2 = glm::normalize(vertices[4] - vertices[0]);     
    glm::vec3 edge3 = glm::normalize(vertices[3] - vertices[0]);     


    axes[0] = edge1;
    axes[1] = edge2;
    axes[2] = edge3;
}

std::array<glm::vec3, 3> Body::GetAxes(){
    return axes;
}

void Body::CheckCollision(Body* other){

    if(isStatic && other->isStatic){
        return;
    }

    glm::vec3 axis;

    //calculate the fucking normal axis:

    glm::vec3 mtvAxis;

    std::array<glm::vec3, 3> axes = GetAxes();
    std::array<glm::vec3, 3> otherAxes = other->GetAxes();

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


    mtvAxis.x *= PI >= orientation.y ? 1 : -1;
    mtvAxis.y *= PI >= orientation.y ? 1 : -1;
    mtvAxis.z *= PI >= orientation.y ? 1 : -1;


    glm::vec3 dirVector = glm::vec3(1);

    if(other->pos.x > pos.x){
        dirVector.x = -1;
    }
    if(other->pos.y < pos.y){
        dirVector.y = -1;
    }
    if(other->pos.z > pos.z){
        dirVector.z = -1;
    }


    glm::vec3 offset = mtvAxis * overlap * -dirVector;

    pos -= offset;

    if(std::signbit(vel.x) == std::signbit(mtvAxis.x) && mtvAxis.x != 0){
        vel.x = 0;
    }
    if(std::signbit(vel.y) == std::signbit(mtvAxis.y) && mtvAxis.y != 0){
        vel.y = 0;
    }
    if(std::signbit(vel.z) == std::signbit(mtvAxis.z) && mtvAxis.z != 0){
        vel.z = 0;
    }

    if(mtvAxis.y == -1){
        isGrounded = true;
    }
    
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

void Body::DrawCollider(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Body::ApplyImpulse(glm::vec3 impulse){
    vel += impulse;
}

void Body::SetVel(glm::vec3 newVel){
    vel = newVel;
}


void Body::RemoveFromSimulation(){
    std::vector<Body*>::iterator selfIndex = std::find(bodies.begin(), bodies.end(), this);
    if(selfIndex == bodies.end()){
        std::cerr << "ERROR: Body not removed from simulation as it is not in it currently" << std::endl;
    }
    bodies.erase(selfIndex);
}

void Body::ReaddToSimulation(){
    bodies.push_back(this);
}


bool Body::IsGrounded(){
    return isGrounded;
}

bool Body::IsStatic(){
    return isStatic;
}


glm::vec3 Body::GetPos(){
    return pos;
}

void Body::SetPos(glm::vec3 newPos){
    pos = newPos;
    UpdateVertices();
}


glm::vec3 Body::GetSize(){
    return size;
}

void Body::SetSize(glm::vec3 newSize){
    size = newSize;
    UpdateVertices();
}


float Body::GetMass(){
    return mass;
}

void Body::SetMass(float newMass){
    mass = newMass;
}


glm::vec3 Body::GetOrientation(){
    return orientation;
}

void Body::SetOrientation(glm::vec3 newOrientation){
    orientation = glm::vec3(fmod(newOrientation.x, 2 * PI), fmod(newOrientation.y, 2 * PI), fmod(newOrientation.z, 2 * PI));
    UpdateVertices();
    CalculateAxes();
}

}

//wana kms https://gamedev.stackexchange.com/questions/44500/how-many-and-which-axes-to-use-for-3d-obb-collision-with-sat