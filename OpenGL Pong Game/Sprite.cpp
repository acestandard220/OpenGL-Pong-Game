#include "Sprite.h"

Sprite::Sprite()
{
    pos = glm::vec3(0.0f, 0.0f, -50.0f);
}

Sprite::Sprite(const Sprite& other)
{
}

Sprite::~Sprite()
{
    //delete texture;
}

bool Sprite::load_sprite(std::string _tex_path)
{
    texture = new Texture2D(_tex_path.c_str());
    return false;
}
