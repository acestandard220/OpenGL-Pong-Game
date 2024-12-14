#include "Texture2D.h"


Texture2D::Texture2D()
{
    data = nullptr;
    std::cout << "Please create the texture with a path\n";
}

Texture2D::Texture2D(const char* texture_path) :path(texture_path)
{
    data = nullptr;
    load_texture();
    create_texture();
}

Texture2D::~Texture2D()
{
    delete data;
}

bool Texture2D::load_texture()
{
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load(path.c_str(), &width, &height, &nChannels, 0);
    if (!data)
    {
        std::cout << "Failed to load texture\n";
        return false;
    }
    return true;
}

bool Texture2D::create_texture()
{
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, get_channel_enum(), width, height, 0, get_channel_enum(), GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
    return false;
}

void Texture2D::bind()
{
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture2D::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

uint32_t Texture2D::get_id()const
{
    return id;
}

GLenum Texture2D::get_channel_enum()
{
    switch (nChannels) {
        case 3:
        {
            return GL_RGB;
        }
        case 4:
        {
            return GL_RGBA;
        }
        default:
            return GL_RGB;
    }
}
