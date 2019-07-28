
#include "Main_Engine.h"
#include "Main_Menu.h"
#include "Screen_GameOver.h"
#include "Screen_Win.h"
#include <SFML/Audio.hpp>
#include "Player1.h"
#include "Monsters.h"



bool gameOver = false;
SaveSystem saveSystem;



tuple<string, int, int> Lua_Manager::window_Data()
{
	lua_State* A = luaL_newstate();
	luaL_dofile(A, "Lua_Manager.lua");
	luaL_openlibs(A);
	lua_pcall(A, 0, 0, 0);

	LuaRef t = getGlobal(A, "window");
	LuaRef title = t["title"];
	LuaRef w = t["width"];
	LuaRef h = t["height"];

	string titleString = title.cast<string>();
	int width = w.cast<int>();
	int height = h.cast<int>();

	tuple<string, int, int> setWindow(titleString, width, height);
	return setWindow;
}

tuple<string> Lua_Manager::player1()
{
	lua_State* B = luaL_newstate();
	luaL_dofile(B, "Lua_Manager.lua");
	luaL_openlibs(B);
	lua_pcall(B, 0, 0, 0);

	LuaRef t = getGlobal(B, "Player1");
	LuaRef texture1 = t["source"];

	string textureString1 = texture1.cast<string>();
	tuple<string> setTexture1(textureString1);
	return setTexture1;
}
tuple<string> Lua_Manager::monster()
{
	lua_State* G = luaL_newstate();
	luaL_dofile(G, "Lua_Manager.lua");
	luaL_openlibs(G);
	lua_pcall(G, 0, 0, 0);

	LuaRef t = getGlobal(G, "Monster");
	LuaRef texture3 = t["source"];

	string textureString3 = texture3.cast<string>();
	tuple<string> setTexture3(textureString3);
	return setTexture3;
}
tuple<string> Lua_Manager::sound2()
{
	lua_State* E = luaL_newstate();
	luaL_dofile(E, "Lua_Manager.lua");
	luaL_openlibs(E);
	lua_pcall(E, 0, 0, 0);

	LuaRef t = getGlobal(E, "Sound2");
	LuaRef sound2 = t["source"];

	string soundString2 = sound2.cast<string>();
	tuple<string> setSound2(soundString2);
	return setSound2;
}

tuple<string> Lua_Manager::npcSet()
{
	lua_State* N = luaL_newstate();
	luaL_dofile(N, "Lua_Manager.lua");
	luaL_openlibs(N);
	lua_pcall(N, 0, 0, 0);

	LuaRef t = getGlobal(N, "Npc");
	LuaRef npc = t["source"];

	string NPCString = npc.cast<string>();
	tuple<string> setNPC(NPCString);
	return setNPC;
}

/*
tuple<string> Lua_Manager::player2()
{
	lua_State* C = luaL_newstate();
	luaL_dofile(C, "Lua_Manager.lua");
	luaL_openlibs(C);
	lua_pcall(C, 0, 0, 0);

	LuaRef t = getGlobal(C, "Player2");
	LuaRef texture2 = t["source"];

	string textureString2 = texture2.cast<string>();
	tuple<string> setTexture2(textureString2);
	return setTexture2;
}
*/
tuple<string> Lua_Manager::sound3()
{
	lua_State* D = luaL_newstate();
	luaL_dofile(D, "Lua_Manager.lua");
	luaL_openlibs(D);
	lua_pcall(D, 0, 0, 0);

	LuaRef t = getGlobal(D, "Sound3");
	LuaRef sound3 = t["source"];

	string soundString3 = sound3.cast<string>();
	tuple<string> setSound3(soundString3);
	return setSound3;
}
/*
tuple<string> Lua_Manager::sound2()
{
	lua_State* F = luaL_newstate();
	luaL_dofile(F, "Lua_Manager.lua");
	luaL_openlibs(F);
	lua_pcall(F, 0, 0, 0);

	LuaRef t = getGlobal(F, "Sound3");
	LuaRef sound3 = t["source"];

	string soundString3 = sound3.cast<string>();
	tuple<string> setSound3(soundString3);
	return setSound3;
}
*/
void main_game::Initialize(sf::RenderWindow* window)
{


	this->font = new sf::Font();
	this->font->loadFromFile("Graphics/font.ttf");
	this->score = new Score_Count(*font, 64U);



	this->lives = new Lives_Count(*font, 64U);
	this->lives->setPosition(window->getSize().x - this->lives->getGlobalBounds().width, 0);
	this->speech = new Quests(*font, 32U, window);

	this->pausedText = new sf::Text("Paused\nPress Escape to Quit", *font, 64U);
	this->pausedText->setOrigin(this->pausedText->getGlobalBounds().width / 2, this->pausedText->getGlobalBounds().height / 2);
	this->pausedText->setPosition(window->getSize().x / 2, window->getSize().y / 2);

	this->paused = false;
	this->enterKey = true;

	manager = new EntityManager();

	map = new Map(manager);

	this->manager->Add("main_guy", new player1(manager, map, saveSystem.x, saveSystem.y));
	map->Load(saveSystem.currentMap, this->speech);

	MenuSoundBuffer1.loadFromFile("../Sounds/Main.ogg");

	mainSound1.setBuffer(MenuSoundBuffer1);

	mainSound1.play();
}
void main_game::Update(sf::RenderWindow* window)
{


	if (this->paused)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return) && !this->enterKey)
		{
			this->paused = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{
			Engine_State.SetState(new Main_Menu());
			return;
		}
	}
	else if (this->speech->speaking)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return) && !this->enterKey)
		{
			this->speech->speaking = false;
		}
	}
	else
	{
		if (!this->manager->Update(window))
		{
			return;
		}

		this->score->Update();
		this->lives->Update();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return) && !this->enterKey)
		{
			this->paused = true;
			this->score->Update();
		}
	}
	if (gameOver || this->lives->Value() <= 0)
	{
		gameOver = false;
		Engine_State.SetState(new Screen_GameOver());
		mainSound1.stop();
		return;
	}
	this->enterKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return);
}
void main_game::Render(sf::RenderWindow* window)
{	


	window->draw(*map);
	this->manager->Render(window);
	window->draw(*this->score);
	window->draw(*this->lives);
	this->speech->Render();

	if (this->paused)
	{
		window->draw(*this->pausedText);
	}
}
void main_game::Destroy(sf::RenderWindow* window)
{
	delete this->score;
	delete this->lives;
	delete this->pausedText;
	delete this->font;

	delete this->manager;
}
