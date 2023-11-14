#version 450 core

layout(location = 0) in vec3 aVertex;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormals;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

out vec2 oTexCoords;
out vec3 oNormalCoords;

out vec4 pos;

void main(){

    pos = model * vec4(aVertex, 1.0);
    gl_Position = projection * view * pos;

    oTexCoords = aTexCoord;
    oNormalCoords = aNormals;

    
}