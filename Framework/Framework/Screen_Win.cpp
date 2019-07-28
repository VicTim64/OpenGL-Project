
#include "Screen_Win.h"
#include "Main_Menu.h"

void Screen_Win::Initialize(sf::RenderWindow* window)
{
	enterKey = false;
	sf::Font* font = new sf::Font();
	font->loadFromFile("Graphics/font.ttf");

	this->winText = new sf::Text("You Win", *font, 100U);
	this->winText->setColor(sf::Color::Green);
	this->winText->setOrigin(sf::Vector2f(this->winText->getGlobalBounds().width / 2, this->winText->getGlobalBounds().height / 2));
	this->winText->setPosition(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));
}
void Screen_Win::Update(sf::RenderWindow* window)
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return) && enterKey)
	{
		Engine_State.SetState(new Main_Menu());
	}
	enterKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return);
}
void Screen_Win::Render(sf::RenderWindow* window)
{
	window->draw(*this->winText);
}
void Screen_Win::Destroy(sf::RenderWindow* window)
{
	delete this->winText;
}
