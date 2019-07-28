#pragma once
#include "Entity_Creator.h"
#include "Map_Creator.h"
#include "Score_Count.h"
#include "Monsters.h"

class Monsters : public Entity
{
public:
	
	Monsters(Map* map, float x, float y);
	bool Update(sf::RenderWindow* window);
	void Collision(Entity* entity);
	int state;
protected:
	Map* map;
	int HP;
	int a;
	int b;
};

