#pragma once
#include "glm/glm.hpp"
#include "Sprite.h"



class Gameobject
{
public:
	Gameobject(glm::vec2 pos, glm::vec2 size, glm::vec2 vel,glm::vec4 col);
	Gameobject(const Gameobject& other) = default;
	virtual ~Gameobject();

	virtual void OnUpdate(float dt) = 0;

	Sprite* sprite;
	glm::vec2 position;
	glm::vec2 size;

	glm::vec4 color;
	glm::vec2 velocity;

};

