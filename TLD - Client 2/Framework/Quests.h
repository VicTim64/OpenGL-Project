#pragma once

#include <SFML/Graphics.hpp>

class Quests : public sf::Text, public sf::Sprite
{
public:
	Quests(sf::Font &font, unsigned int size, sf::RenderWindow* window);
	bool speaking;
	void SetText(std::string text);
	void Render();
private:
	sf::Texture* texture;
	sf::RenderWindow* window;
};


