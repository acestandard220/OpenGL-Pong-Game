#include "Ball.h"

Ball::Ball()
	: Gameobject({ 0.0f,0.0f }, glm::vec2(0.2f), { 5.0f,2.0f }, { 1.0f,0.0f,0.0f,1.0f })
{
}

Ball::Ball(glm::vec2 pos,float diameter,glm::vec2 vel, glm::vec4 color)
	: Gameobject(pos,glm::vec2(diameter),vel,color) , diameter(diameter)
{
	center = {
		pos.x + (diameter / 2),
		pos.y + (diameter / 2)
	};

	sprite = new Sprite;
	sprite->load_sprite("awesomeface.png");
}

Ball::~Ball()
{
}

void Ball::OnUpdate(float dt)
{
	center = {
		position.x + (diameter / 2),
		position.y + (diameter / 2)
	};
}
