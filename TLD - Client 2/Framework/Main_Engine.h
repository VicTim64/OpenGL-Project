#pragma once
//#pragma warning(disable : 4996)
#include "Entity_Manage.h"
#include "Engine_State.h"
#include "Score_Count.h"
#include "Lives_Count.h"
#include "Quests.h"
#include <SFML/Audio.hpp>

#include "Map_Creator.h"

#include "Save_System.h"

#define ENEMY_AMMO 5
#define PLAYER_AMMO 3

#include <tuple>
#include <iostream>
#include <lua.hpp>
#include <LuaBridge\LuaBridge.h>

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

using namespace luabridge;
using namespace std;

extern bool gameOver;
extern SaveSystem saveSystem;


class Lua_Manager
{
public:
	Lua_Manager() {};
	~Lua_Manager() {};
	tuple<string, int, int> window_Data();
	tuple<string> player1();
	tuple<string> monster();
	//tuple<string> player2();
	tuple<string> sound3();
	tuple<string> npcSet();
	tuple<string> sound2();

	vector<string> getElements(const string& table, lua_State* L);
};

class main_game : public side_State
{
public:
	
	void Initialize(sf::RenderWindow* window);
	void Update(sf::RenderWindow* window);
	void Render(sf::RenderWindow* window);
	void Destroy(sf::RenderWindow* window);

private:

	Score_Count* score;
	Lives_Count* lives;
	Quests* speech;
	sf::Text* pausedText;
	sf::SoundBuffer MenuSoundBuffer1;
	sf::Sound mainSound1;
	
	sf::Font* font;

	bool paused, enterKey;

	EntityManager* manager;

	Map* map;
};