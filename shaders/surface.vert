#version 450 core

layout(location = 0) in vec2 aVertex;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

uniform int billboard;

out vec2 aTexCoords;

void main(){
    mat4 modelViewMatrix = view * model;
    if(billboard == 1){
        modelViewMatrix[0][0] = 1;
        modelViewMatrix[0][1] = 0;
        modelViewMatrix[0][2] = 0;

        modelViewMatrix[1][0] = 0;
        modelViewMatrix[1][1] = 1;
        modelViewMatrix[1][2] = 0;

        modelViewMatrix[2][0] = 0;
        modelViewMatrix[2][1] = 0;
        modelViewMatrix[2][2] = 1;
    }
    gl_Position = projection * modelViewMatrix *  vec4(aVertex, 0.0, 1.0);
    aTexCoords = aVertex + vec2(0.5, 0.5);
}