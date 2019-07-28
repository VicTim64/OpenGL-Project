#pragma once

#include "Entity_Creator.h"
#include "Map_Creator.h"

//A class made for the NPC that I have accross the map/s
// Easier to call them in other classes this way

class NPC_Creator : public Entity
{
public:
	NPC_Creator(Quests* speech, Map* map, float x, float y);
	bool Update(sf::RenderWindow* window);
	void Collision(Entity* entity);
protected:
	std::string text;
	Map* map;
private:
	Quests* speech;
};

