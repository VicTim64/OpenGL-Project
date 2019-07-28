#pragma once

#include "Monsters.h"
#include "Entity_Creator.h"

class Monster1 : public Monsters
{
public:
	Monster1(Map* map, float x, float y) : Monsters(map, x, y)
	{
		
	}
};