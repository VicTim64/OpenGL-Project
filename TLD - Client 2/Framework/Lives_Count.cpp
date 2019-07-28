
#include "Lives_Count.h"

Lives_Count::Lives_Count(sf::Font &font, unsigned int size) : sf::Text("Lives: 3", font, size)
{
	this->value = 3;
}

void Lives_Count::RemoveLife()
{
	this->value -= 1;
}

int Lives_Count::Value()
{
	return this->value;
}

void Lives_Count::Update()
{
	this->setString("Lives: " + std::to_string(this->value));
}