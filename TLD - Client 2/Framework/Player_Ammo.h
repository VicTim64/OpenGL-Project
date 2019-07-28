#pragma once

#include "Ammo.h"

class Player_Ammo : public Ammo
{
public:
	Player_Ammo(Map* map, float x, float y, float direction, float distance) : Ammo(map, x, y, direction, distance)
	{
		this->groupId = 4;
		this->setColor(sf::Color::Black);
	}
};