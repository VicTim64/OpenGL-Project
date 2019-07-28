
#include "Main_Engine.h"
#include "NPC_Creator.h"

NPC_Creator::NPC_Creator(Quests* speech, Map* map, float x, float y)
{
	Lua_Manager npcData;
	tuple<string> npcSet = npcData.npcSet();
	this->Load(get<0>(npcSet));
	
	this->setPosition(x, y);
	this->setColor(sf::Color::Cyan);
	this->map = map;
	this->groupId = 3;
	this->speech = speech;
}

bool NPC_Creator::Update(sf::RenderWindow* window)
{
	Entity::Update(window);
	return true;
}

void NPC_Creator::Collision(Entity* entity)
{
	switch (entity->GroupID())
	{
	case 2:
		speech->SetText(this->text);
		entity->Destroy();
		break;
	}
}

