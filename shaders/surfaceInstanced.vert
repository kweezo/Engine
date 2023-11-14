#version 450 core

layout(location = 0) in vec2 aVertex;
layout(location = 1) in vec4 m1;
layout(location = 2) in vec4 m2;
layout(location = 3) in vec4 m3;
layout(location = 4) in vec4 m4;

out vec2 aTexCoords;

uniform mat4 view;
uniform mat4 projection;

void main(){
    mat4 model = mat4(m1, m2, m3, m4);

    gl_Position = projection * view * model * vec4(aVertex, 0.0, 1.0);
    aTexCoords = aVertex + vec2(0.5, 0.5);
}