#pragma once
#include <SFML/Graphics.hpp>

class Lives_Count : public sf::Text
{
public:
	Lives_Count(sf::Font &font, unsigned int size);
	void RemoveLife();
	void Update();
	int Value();
private:
	int value;
};