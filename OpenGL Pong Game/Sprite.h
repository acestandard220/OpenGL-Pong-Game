#pragma once
#include "Texture2D.h"
#include "glm/matrix.hpp"


class Sprite
{
public:
	Sprite();
	Sprite(const Sprite& other);
	~Sprite();

	bool load_sprite(std::string _tex_path);

	uint32_t get_texture_id() { return texture->get_id(); }
    int get_texture_width() { return texture->get_width(); }
    int get_texture_height() { return texture->get_height(); }
   
	int width;
	int height;
	glm::vec3 pos;

    private:
		Texture2D* texture;
};

