#pragma once
#include "Gameobject.h"

class Ball : public Gameobject
{
public:
	Ball();
	Ball(glm::vec2 pos, float diameter, glm::vec2 vel, glm::vec4 color);
	virtual ~Ball();

	float diameter;
	glm::vec2 center;

	virtual void OnUpdate(float dt) override;
};

