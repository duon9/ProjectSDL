#pragma once
#include "interact_obj.h"
#include "math.h"
#include "dialogue_box.h"

class NPC : public Object
{
protected:
	DialogueBox& box = DialogueBox::getInstance();
	std::vector<std::string> dialogue;
public:
	NPC(SDL_Renderer* renderer, std::string type) : Object(renderer) {
		this->type = type;
	}

	~NPC() {

	}
	//virtual void setProtocolCode() override;
	virtual void listen(SDL_Event* e) override;
	virtual void update();
	virtual void updateDialogue(const std::vector<std::string>& content);
};

