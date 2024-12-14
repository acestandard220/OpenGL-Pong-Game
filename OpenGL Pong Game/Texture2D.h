#pragma once
#include <iostream>
#include "GL/glew.h"
#include "stb_image.h"

class Texture2D
{
public:

	Texture2D();
	Texture2D(const char* texture_path);
	~Texture2D();

	bool load_texture();
	bool create_texture();
	void bind();
	void unbind();

	uint32_t get_id()const;
	int get_width() { return width; }
	int get_height() { return height; }

private:
	GLenum get_channel_enum();
private:
	int height;
	int width;
	int nChannels;

	unsigned char* data;

	uint32_t id;
	std::string path;
};

