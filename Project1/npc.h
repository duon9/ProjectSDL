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
		//dialogue.push_back("Nothing to talk to you");
	}

	~NPC() {

	}
	//virtual void setProtocolCode() override;
	virtual void listen(SDL_Event* e) override;
	virtual void update();
	virtual void updateDialogue(const std::vector<std::string>& content);
	virtual void add(std::string content);
	virtual void link(std::vector<std::string> content);
};

