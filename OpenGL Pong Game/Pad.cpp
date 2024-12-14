#include "Pad.h"

Pad::Pad() 
	: Gameobject({0.0f,0.0f},{1.0f,2.0f},{5.0f,2.0f},{1.0f,0.0f,0.0f,1.0f})
{
}

Pad::Pad(glm::vec2 pos, glm::vec2 size, glm::vec2 vel, glm::vec4 col) 
	: Gameobject(pos,size,vel,col)
{
	sprite = new Sprite;
	sprite->load_sprite("meme.jpeg");
}

Pad::~Pad()
{
}

void Pad::OnUpdate(float dt)
{
	
}


