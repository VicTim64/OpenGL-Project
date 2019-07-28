#include <iostream>
#include "Main_Menu.h"
#include "Main_Engine.h"
#include "Map_Creator.h"
#include "Entity_Creator.h"
#include"Entity_Manage.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;



void Main_Menu::Initialize(sf::RenderWindow* window)
{
	this->selected = 0;

	this->font = new sf::Font();
	this->font->loadFromFile("Graphics/font.ttf");

	this->title = new sf::Text("TLD : AnomalYlamonA", *this->font, 200U);
	this->title->setOrigin(this->title->getGlobalBounds().width / 2, this->title->getGlobalBounds().height / 2);
	this->title->setPosition(window->getSize().x / 2, window->getSize().y / 8);

	this->play = new sf::Text("Begin Game", *this->font, 128U);
	this->play->setOrigin(this->play->getGlobalBounds().width / 2, this->play->getGlobalBounds().height / 2);
	this->play->setPosition(window->getSize().x / 2, window->getSize().y / 2);

	this->quit = new sf::Text("Exit Game", *this->font, 128U);
	this->quit->setOrigin(this->quit->getGlobalBounds().width / 2, this->quit->getGlobalBounds().height / 2);
	this->quit->setPosition(window->getSize().x / 2, window->getSize().y / 2 + this->play->getGlobalBounds().height);

	Lua_Manager sound2Data;
	tuple<string> sound2 = sound2Data.sound2();

	MenuSoundBuffer.loadFromFile(get<0>(sound2));
	mainSound.setBuffer(MenuSoundBuffer);
	mainSound.play();
	

}
void Main_Menu::Update(sf::RenderWindow* window)
{



	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && !this->upKey)
	{

		this->selected -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && !this->downKey)
	{
		this->selected += 1;
	}
	if (this->selected > 1)
	{
		this->selected = 0;
	}
	if (this->selected < 0)
	{
		this->selected = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return))
	{
		switch (this->selected)
		{
		case 0:
			Engine_State.SetState(new main_game());
			mainSound.stop();
			break;
		case 1:
			quitGame = true;
			break;
		}
	}
	this->upKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
	this->downKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);


}
void Main_Menu::Render(sf::RenderWindow* window)
{
	
	this->play->setColor(sf::Color::White);
	this->quit->setColor(sf::Color::White);
	switch (this->selected)
	{
	case 0:
		this->play->setColor(sf::Color::Green);
		break;
	case 1:
		this->quit->setColor(sf::Color::Green);
		break;
	}

	window->draw(*this->title);
	window->draw(*this->play);
	window->draw(*this->quit);



}


void Main_Menu::Destroy(sf::RenderWindow* window)
{
	delete this->font;
	delete this->title;
	delete this->play;
	delete this->quit;
	//delete this->mainSound;

}
