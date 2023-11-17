#version 450 core

uniform sampler2D baseTex;
uniform sampler2D normalTex;

uniform vec3 colorModifier;

uniform vec3 globalLightOrientation;
uniform vec3 globalLightColor;
uniform float globalLightBrightness;

out vec4 color;

in vec2 oTexCoords;
in vec3 oNormalCoords;

in vec4 pos;

void main(){
    vec3 lightPos = {cos(globalLightOrientation.x), sin(globalLightOrientation.y), tan(globalLightOrientation.z)};
    lightPos *= pos.xyz;

    float diff = dot(normalize(oNormalCoords), normalize(lightPos)*2);

    if(diff < 0.7){
        diff = 0.7;
    }

    color = texture(baseTex, oTexCoords) * (texture(normalTex, oNormalCoords.xy) * 0.5 + 0.5) * vec4(colorModifier, 1.0); 
    color *= vec4(globalLightColor * diff, 1.0f) * globalLightBrightness;

//    color = vec4(oTexCoords, 0.0, 1.0);

}