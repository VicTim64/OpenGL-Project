#pragma once

#include "Entity_Creator.h"
#include "Map_Creator.h"
#include<SFML/Audio.hpp>

extern SaveSystem saveSystem;

class player2 : public Entity
{
public:
	player2(EntityManager* entityManager, Map* map, float x, float y);
	bool Update(sf::RenderWindow* window);
	void Collision(Entity* entity);
private:
	Map* map;
	float speed;
	EntityManager* entityManager;
	bool spaceKey, xKey;
	float direction;
	sf::Sound hit;
	sf::SoundBuffer hitBuffer;


};

