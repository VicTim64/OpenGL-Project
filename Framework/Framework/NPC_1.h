#pragma once

#include "NPC_Creator.h"

class Npc1 : public NPC_Creator
{
public:
	Npc1(Quests* speech, Map* map, float x, float y) : NPC_Creator(speech, map, x, y)
	{
		this->text = "Vy! We need to hold the possition and wait for backup!";
	}
};