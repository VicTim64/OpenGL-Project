
#include "Ammo.h"

Ammo::Ammo(Map* map, float x, float y, float direction, float distance)
{
	this->active = 1;
	this->groupId = 2;
	this->Load("Ammo.png");
	this->setColor(sf::Color::Transparent);
	this->setScale(0.25f, 0.25f);
	this->velocity.x = cos(direction / 180.0f * 3.14f) * 3;
	this->velocity.y = sin(direction / 180.0f * 3.14f) * 3;
	this->setPosition(x + this->getGlobalBounds().width, y + this->getGlobalBounds().height);
	this->dist = distance;
	this->map = map;
}

bool Ammo::Update(sf::RenderWindow* window)
{
	if (this->getPosition().y <= 0 || this->getPosition().y + this->getGlobalBounds().height >= window->getSize().y)
	{
		this->Destroy();
	}
	this->dist -= sqrt(this->velocity.x * this->velocity.x + this->velocity.y * this->velocity.y);
	if (this->dist <= 0)
	{
		this->Destroy();
	}
	if (this->map->CheckCollision(this, NONE) > 2)
	{
		this->Destroy();
	}
	Entity::Update(window);
	return true;
}

void Ammo::Collision(Entity* entity)
{
}
