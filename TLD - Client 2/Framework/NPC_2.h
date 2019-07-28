#pragma once

#include "NPC_Creator.h"

class Npc2 : public NPC_Creator
{
public:
	Npc2(Quests* speech, Map* map, float x, float y) : NPC_Creator(speech, map, x, y)
	{
		this->text = "Vy`Kah, The space station is under attack by Dolkyrs! Clear the area!";
		this->setColor(sf::Color::Magenta);
	}
};