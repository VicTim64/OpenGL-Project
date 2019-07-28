
#include "Main_Engine.h"
#include "Player1.h"
#include "Ammo.h"
#include "Player_Ammo.h"
#include "Monsters.h"
#include <SFML/Audio.hpp>

player1::player1(EntityManager* entityManager, Map* map, float x, float y)
{

	Lua_Manager player1Data;
	tuple<string> player1 = player1Data.player1();
	
	this->Load(get<0>(player1));
	this->setPosition(x, y);
	this->map = map;
	this->speed = 1.0f;
	this->groupId = 1;
	this->entityManager = entityManager;

	// Prepare the hit sound
	Lua_Manager sound3Data;
	tuple<string> sound3 = sound3Data.sound3();

	hitBuffer.loadFromFile(get<0>(sound3));
	hit.setBuffer(hitBuffer);
}

bool player1::Update(sf::RenderWindow* window)
{
	this->velocity.x = (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) - sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) * this->speed;
	this->velocity.y = (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) - sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) * this->speed;

	if (this->velocity.x > 0)
	{
		if (this->velocity.y > 0)
		{
			this->direction = 45.0f;
		}
		else if (this->velocity.y < 0)
		{
			this->direction = 315.0f;
		}
		else
		{
			this->direction = 0.0f;
		}
	}
	else if (this->velocity.x < 0)
	{
		if (this->velocity.y > 0)
		{
			this->direction = 135.0f;
		}
		else if (this->velocity.y < 0)
		{
			this->direction = 225.0f;
		}
		else
		{
			this->direction = 180.0f;
		}
	}
	else
	{
		if (this->velocity.y > 0)
		{
			this->direction = 90.0f;
		}
		else if (this->velocity.y < 0)
		{
			this->direction = 270.0f;
		}
	}

	if (this->getPosition().y <= 0)
	{
		saveSystem.currentMap = map->topArea;
		saveSystem.x = this->getPosition().x;
		saveSystem.y = window->getSize().y - this->getGlobalBounds().height - 32;
		Engine_State.SetState(new main_game());
		return false;
	}
	if (this->getPosition().y + this->getGlobalBounds().height >= window->getSize().y)
	{
		saveSystem.currentMap = map->bottomArea;
		saveSystem.x = this->getPosition().x;
		saveSystem.y = 32;
		Engine_State.SetState(new main_game());
		return false;
	}
	if (this->getPosition().x <= 0)
	{
		saveSystem.currentMap = map->leftArea;
		saveSystem.x = window->getSize().x - this->getGlobalBounds().width - 32;
		saveSystem.y = this->getPosition().y;
		Engine_State.SetState(new main_game());
		return false;
	}
	if (this->getPosition().x + this->getGlobalBounds().width >= window->getSize().x)
	{
		saveSystem.currentMap = map->rightArea;
		saveSystem.x = 32;
		saveSystem.y = this->getPosition().y;
		Engine_State.SetState(new main_game());
		return false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !this->spaceKey)
	{
		this->entityManager->Add("bullet", new Ammo(this->map, this->getPosition().x, this->getPosition().y, direction, 32));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X) && !this->xKey)
	{
		this->entityManager->Add("pBullet", new Player_Ammo(this->map, this->getPosition().x, this->getPosition().y, direction, 800));
		////////////////
		hit.play();
	}

	switch (this->map->CheckCollision(this, NONE))
	{
	case 0:
		break;
	case 1:
		this->speed = 1.0f;
		this->setColor(sf::Color::White);
		break;
	case 2:
		this->speed = 0.5f;
		this->setColor(sf::Color::Red);
		break;
	}

	if (this->map->CheckCollision(this, LEFT) > 2)
	{
		this->move(-abs(this->speed), 0);
	}
	if (this->map->CheckCollision(this, RIGHT) > 2)
	{
		this->move(abs(this->speed), 0);
	}
	if (this->map->CheckCollision(this, UP) > 2)
	{
		this->move(0, abs(this->speed));
	}
	if (this->map->CheckCollision(this, DOWN) > 2)
	{
		this->move(0, -abs(this->speed));
	}

	this->spaceKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);

	this->xKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X);

	Entity::Update(window);
	return true;
}


void player1::Collision(Entity* entity)
{
	switch (entity->GroupID())
	{
	case 3:
		this->move(-this->velocity.x, -this->velocity.y);
		break;
	case 5:
		Monsters* temp = reinterpret_cast<Monsters*>(entity);
		temp->state = 5;

		sf::Color seeThrough = temp->getColor();
		seeThrough.a = 128;
		temp->setColor(seeThrough);
		break;
	}
}
