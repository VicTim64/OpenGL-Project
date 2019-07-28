#pragma once

#include "Entity_Creator.h"
#include "Map_Creator.h"

class Ammo : public Entity
{
public:
	Ammo(Map* map, float x, float y, float direction, float distance);
	bool Update(sf::RenderWindow* window);
	void Collision(Entity* entity);
private:
	Map* map;
	float dist;
};