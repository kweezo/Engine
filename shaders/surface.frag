#version 450 core

uniform sampler2D tex;

out vec4 color;

in vec2 aTexCoords;

void main(){
    color = texture(tex, aTexCoords);
}