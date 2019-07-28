#pragma once
#pragma warning(disable : 4996)
#include <sstream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Engine_State.h"

class Main_Menu : public side_State
{
public:
	void Initialize(sf::RenderWindow* window);
	void Update(sf::RenderWindow* window);
	void Render(sf::RenderWindow* window);
	void Destroy(sf::RenderWindow* window);

		// Initiate the Main Menu sound

private:

	sf::SoundBuffer MenuSoundBuffer;
	sf::Sound mainSound;
	sf::Font* font;
	sf::Text* title;
	sf::Text* play;
	sf::Text* quit;
	sf::Sprite _background;
	sf::Sprite _title;
	sf::Sprite _playButton;
	sf::Sprite _quitButton;

	int selected;

	bool upKey, downKey;
};