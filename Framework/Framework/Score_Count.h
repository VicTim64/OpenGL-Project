#pragma once
#include <SFML/Graphics.hpp>

class Score_Count : public sf::Text
{
public:
	Score_Count(sf::Font &font, unsigned int size);
	void IncrementScore();
	void Update();
private:
	int value;
};