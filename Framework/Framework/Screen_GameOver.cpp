
#include "Screen_GameOver.h"
#include "Main_Menu.h"

void Screen_GameOver::Initialize(sf::RenderWindow* window)
{
	enterKey = false;
	sf::Font* font = new sf::Font();
	font->loadFromFile("Graphics/font.ttf");

	this->gameOverText = new sf::Text("Game Over", *font, 100U);
	this->gameOverText->setColor(sf::Color::Red);
	this->gameOverText->setOrigin(sf::Vector2f(this->gameOverText->getGlobalBounds().width / 2, this->gameOverText->getGlobalBounds().height / 2));
	this->gameOverText->setPosition(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));
}
void Screen_GameOver::Update(sf::RenderWindow* window)
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return) && enterKey)
	{
		Engine_State.SetState(new Main_Menu());
	}
	enterKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return);
}
void Screen_GameOver::Render(sf::RenderWindow* window)
{
	window->draw(*this->gameOverText);
}
void Screen_GameOver::Destroy(sf::RenderWindow* window)
{
	delete this->gameOverText;
}
