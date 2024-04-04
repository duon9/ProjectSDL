#pragma once
#include "interact_obj.h"
#include "math.h"
#include "dialogue_box.h"

class NPC : public Object
{
private:
	DialogueBox& box = DialogueBox::getInstance();
public:
	NPC(SDL_Renderer* renderer, std::string type) : Object(renderer) {
		this->type = type;
	}

	~NPC() {

	}
	//virtual void setProtocolCode() override;
	virtual void listen(SDL_Event* e) override;
};

