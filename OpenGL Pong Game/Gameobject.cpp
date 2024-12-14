#include "Gameobject.h"

Gameobject::Gameobject(glm::vec2 pos, glm::vec2 siz, glm::vec2 vel, glm::vec4 col)
	:position(pos),size(siz),velocity(vel),color(col)
{
}

Gameobject::~Gameobject()
{
	delete sprite;
}
