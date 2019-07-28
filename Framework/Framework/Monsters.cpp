#include "Main_Engine.h"
#include "Monsters.h"
#include "Score_Count.h"



Monsters::Monsters(Map* map, float x, float y)
{
	Lua_Manager monsterData;
	tuple<string> monster = monsterData.monster();

	this->Load(get<0>(monster));
	this->setPosition(x, y);
	this->setColor(sf::Color::Red);
	this->map = map;
	this->groupId = 5;
	this->HP = 4;
	this->state = 0;
	this->a = 1;
}

bool Monsters::Update(sf::RenderWindow* window)
{
	if (this->HP <= 0)
	{
		this->Destroy();

		
	}

	if (state == 0)
	{
		sf::Color seeThrough = this->getColor();
		seeThrough.a = 255;
		this->setColor(seeThrough);


	}
	else if (state > 0)
	{
		state -= 1;
	}

	Entity::Update(window);
	return true;
}



void Monsters::Collision(Entity* entity)
{
	switch (entity->GroupID())
	{
	case 4:
		entity->Destroy();
		this->HP -= 1;
		this->a += 1;

		std::cout << "a: " << a;
		break;
	}
	
}

