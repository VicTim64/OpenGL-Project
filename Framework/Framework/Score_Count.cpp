#include "Score_Count.h"
#include <iostream>
#include "Monsters.h"

Score_Count::Score_Count(sf::Font &font, unsigned int size) : sf::Text("Score: 0", font, size)
{
	this->value = 10;
}

void Score_Count::IncrementScore()
{

	this->value += 5;
}

void Score_Count::Update()
{
	this->setString("Score: " + std::to_string(this->value));
	std::string Val = std::to_string(this->value);

//	std::cout << "score is:" << this->value;
}