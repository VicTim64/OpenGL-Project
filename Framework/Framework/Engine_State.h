#pragma once


#include <SFML/Graphics.hpp>

#include "Save_System.h"

extern SaveSystem saveSystem;

class side_State
{
public:
	virtual void Initialize(sf::RenderWindow* window)
	{
	}

	virtual void Update(sf::RenderWindow* window)
	{
	}

	virtual void Render(sf::RenderWindow* window)
	{
	}

	virtual void Destroy(sf::RenderWindow* window)
	{
	}
};

class game_state
{
public:
	game_state()
	{
		this->state = NULL;
	}

	void SetWindow(sf::RenderWindow* window)
	{
		this->window = window;
	}

	void SetState(side_State* state)
	{
		if (this->state != NULL)
		{
			this->state->Destroy(this->window);
		}
		saveSystem.Save();
		this->state = state;
		if (this->state != NULL)
		{
			this->state->Initialize(this->window);
		}
	}

	void Update()
	{
		if (this->state != NULL)
		{
			this->state->Update(this->window);
		}
	}
	void Render()
	{
		if (this->state != NULL)
		{
			this->state->Render(this->window);
		}
	}

	~game_state()
	{
		if (this->state != NULL)
		{
			this->state->Destroy(this->window);
		}
	}
private:
	sf::RenderWindow* window;
	side_State* state;
};

extern game_state Engine_State;
extern bool quitGame;

