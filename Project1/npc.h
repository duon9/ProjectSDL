#pragma once
#include "interact_obj.h"

class NPC : public Object
{
private:

public:
	NPC(SDL_Renderer* renderer, std::string type) : Object(renderer) {
		this->type = type;
	}

	~NPC() {

	}
	//virtual void setProtocolCode() override;
	
};

