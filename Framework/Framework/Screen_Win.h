#pragma once
#pragma warning(disable : 4996)
#include "Engine_State.h"

class Screen_Win : public side_State
{
public:
	void Initialize(sf::RenderWindow* window);
	void Update(sf::RenderWindow* window);
	void Render(sf::RenderWindow* window);
	void Destroy(sf::RenderWindow* window);
private:
	sf::Text* winText;
	bool enterKey;
};
