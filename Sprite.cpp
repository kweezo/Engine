#include "Sprite.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Engine{


Sprite::Sprite(std::string path){
    LoadSprite(path);
}

void Sprite::LoadSprite(std::string path){
    stbi_set_flip_vertically_on_load(true);

    int channels;

    data = stbi_load(path.c_str(), &x, &y, &channels, 4);

    if(!data){
        if(!path.empty()){
            std::cerr << "Failed to load sprite with path " << path << std::endl;
        }
        data = stbi_load("res/white_pixel.png", &x, &y, &channels, 4);
    }

}

void Sprite::CreateTexture(){
    tex.reset(new GLuint);



    glCreateTextures(GL_TEXTURE_2D, 1, tex.get());
    glBindTexture(GL_TEXTURE_2D, tex.get()[0]);


    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);

}

GLuint Sprite::GetRawTextureHandle(){
    return tex.get()[0];
}

void Sprite::BindTexture(uint32_t loc){
    glActiveTexture(loc);
    glBindTexture(GL_TEXTURE_2D, tex.get()[0]);
}

Sprite::~Sprite(){
    if(tex.use_count() == 1){
        glDeleteTextures(1, tex.get());
    }
}

Sprite::Sprite(const Sprite& other){
    CopyFrom(other);
}

Sprite& Sprite::operator=(const Sprite& other){
    if(this == &other){
        return *this;
    }

    CopyFrom(other);

    return *this;
}

void Sprite::CopyFrom(const Sprite& other){
    tex = other.tex;
    data = other.data;
    x = other.x;
    y = other.y;
}

void Sprite::operator()(std::string path){
    LoadSprite(path);
}


}

