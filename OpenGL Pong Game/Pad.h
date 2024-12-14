#pragma once
#include "Gameobject.h"

class Pad : public Gameobject
{
    public:
		Pad();
	    Pad(glm::vec2 pos,glm::vec2 size,glm::vec2 vel,glm::vec4 col);
	    virtual ~Pad();
		
		virtual void OnUpdate(float dt) override;

    private:
		

};