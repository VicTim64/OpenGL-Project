#pragma once

#include "Monsters.h"

class Monster2 : public Monsters
{
public:
	Monster2(Map* map, float x, float y) : Monsters(map, x, y)
	{
	}
};