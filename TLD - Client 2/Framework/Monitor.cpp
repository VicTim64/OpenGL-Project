#pragma warning(disable : 4996)
//#include <Windows.h> // windows.h not working with enet library
//Initialise Endgine
#include "Engine_State.h"
//Enter Main Menu
#include "Main_Menu.h"
#include "Monitor.h"
//SFML Libraries
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
// Serial View
#include <iostream>
//  ENET LIBRARY
#include <enet\enet.h>
// 
#include "Main_Engine.h"

// Used for cmd info
using namespace std; 
//
#include <tuple>

// Used for Audio & Graphics
using namespace sf; 
//

game_state Engine_State; //Create Engine Object.
bool quitGame = false;

// ENET VECTOR FOR POSSITION !
//We send the data possition to the server and update it!
struct Vector2ENETClient {
	float x;
	float y;
};
// Server sends the data back
struct Vector2ENETServer{
	float x;
	float y;
};


int main()
{



	Lua_Manager luaData;
	tuple<string, int, int> window_Data = luaData.window_Data();

	RenderWindow window(VideoMode(get<1>(window_Data), get<2>(window_Data)), get<0>(window_Data));

	//sf::RenderWindow window(sf::VideoMode(1280, 768), "TLD : Anomal|yamonA");

	Engine_State.SetWindow(&window);
	Engine_State.SetState(new Main_Menu());


	//
	// ENET SETUP BEGIN // ENET SETUP BEGIN // ENET SETUP BEGIN // ENET SETUP BEGIN // ENET SETUP BEGIN // ENET SETUP BEGIN //
	//
	Vector2ENETServer position;
	position.x = 600.0f;
	position.y = 100.0f;
	// We create an instance for the PLAYER 2! 

	sf::RectangleShape enemy;
	enemy.setSize(sf::Vector2f(100.0f, 100.0f));
	enemy.setPosition(sf::Vector2f(position.x, position.y));
	sf::Texture testTexture;
	if (!testTexture.loadFromFile("../Player2/keyboardcat.jpg"))
	{
		cout << "Texture did not load!" << "\n";
	}
	enemy.setTexture(&testTexture);
	// We create an instance for the PLAYER 2!

	if (enet_initialize() != 0)
	{
		cout << "Enet failed to initialise!" << "\n\n";
	}

	/* Much of this will be familiar from the server code. What differs
	is the inclusion of an Peer. This is basically ENet's way of tracking
	what you're connected to. Since our Client will be initialising the
	connection, they need a peer to store information about the server they're
	connecting to. */

	ENetAddress address;
	ENetHost* client;
	ENetHost* server;
	ENetPeer* peer;
	ENetEvent enetEvent;

	ENetPacket* dataPacket;

	client = enet_host_create(NULL, 1, 2, 0, 0);
	address.host = ENET_HOST_ANY;
	address.port = 1234;

	if (client == NULL)
	{
		cout << "Client failed to initialise!" << "\n\n";
	}

	server = enet_host_create(&address, 32, 2, 0, 0); // server

	enet_address_set_host(&address, "localhost"); // client
	

	/* Now we're trying to connect to the server. We include who we are,
	the address to establish the connection to, the number of channels, and a
	generic data variable we can use to say something to the server (currently 0). */

	peer = enet_host_connect(client, &address, 2, 0);
	
	if (server == NULL)
	{
		cout << "Server failed to initialise!" << "\n\n";
	}
	
	if (peer == NULL) {
		cout << "No available peers for initializing an ENet connection.\n";
	}

	/* To make our lives a little easier, we declare this newPosition variable on
	the heap. It's where the data from our received packet is going to be stored,
	if it reaches us. */

	Vector2ENETClient* newPosition = new Vector2ENETClient;

	


	//
	// ENET SETUP END // ENET SETUP END // ENET SETUP END // ENET SETUP END // ENET SETUP END // ENET SETUP END 
	//

	while (window.isOpen())
	{
		

		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
			{

				if (peer != NULL)
				{
					enet_peer_disconnect_now(peer, 0);
					window.close();
				}
			}
		}
		while (enet_host_service(server, &enetEvent, 0) > 0)
		{
			switch (enetEvent.type)
			{
			case ENET_EVENT_TYPE_CONNECT:

				cout << "A client connected from address " << enetEvent.peer->address.host << ":" << enetEvent.peer->address.port << ".\n";

				/* This event type has an associated peer: the client which has
				connected to the server. We can store some data about this peer
				for as long as it remains in scope using the "data" variable. */

				enetEvent.peer->data = "This is a client";

				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				cout << "The client from address " << enetEvent.peer->address.host << ":" << enetEvent.peer->address.port << " disconnected \n";

				enetEvent.peer->data = NULL;

				break;
			}
		}

		while (enet_host_service(client, &enetEvent, 0) > 0)
		{
			switch (enetEvent.type) {

				/* Again, we're reacting based on the detected event type. In this case, it's
				ENET_EVENT_TYPE_RECEIVE, which means our client has recieved a packet from a
				peer (in this case, the server). After quickly outputting some debug text to
				console to confirm packet receipt, what happens next is the key part.

				Our packet has some intrinsic variables - its data (what it's storing) and its
				dataLength (how much data it's storing). In this case, since we KNOW the packet
				is a Vector2, we can use the memcpy function fairly easily. This is a basic C++
				function which copies a given amount of data from one location to another. In
				this case, it copies TO newPosition FROM data, and it copies an amount dataLength.

				Given what we know about pointer arithmetic, it should be obvious to us that we
				can make these packets more sophisticated. We can make huge packets which hold
				many different kinds of data. We simply include an enumerator at the beginning of
				each data segment, saying what data type it is, and either copy that much data over
				into a variable of that type, or include as the next element of a packet the amount
				of data this variable type needs to copy. This is particularly useful when it comes
				to Part 2 of the coursework, where 'level data' is likely very different to the
				'physics data' you'll have been transmitting for Part 1. */

			case ENET_EVENT_TYPE_RECEIVE:
				cout << "Packet received!\n";
				memcpy(newPosition, enetEvent.packet->data, enetEvent.packet->dataLength);
				cout << newPosition->x << "," << newPosition->y << "\n";
				enemy.setPosition(sf::Vector2f(newPosition->x, newPosition->y));
				break;
			}
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				position.x += -1.6f;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				position.x += 1.6f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				position.y += -1.6f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				position.y += 1.6f;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}
			enemy.setPosition(sf::Vector2f(position.x, position.y));
			cout << "The position of the entity is (" << position.x << "," << position.y << ")\n";

			/* We populate the packet we made earlier using the enet_packet_create function, which accepts
			a reference to our Vector 2, the size of the data being sent (so, one Vector2 in this case), and
			flags whether or not the packet receipt needs verifying (in this example, we say that it does,
			but in reality it doesn't necessarily need to). The host then broadcasts the data packet to all
			connected clients across Channel 0. */

			dataPacket = enet_packet_create(&position, sizeof(Vector2ENETServer), ENET_PACKET_FLAG_RELIABLE);
			enet_host_broadcast(server, 0, dataPacket);
		}
		//window.clear(sf::Color::Black);

		Engine_State.Update();
		Engine_State.Render();

		//window.display();

		if (quitGame)
		{
			if (peer != NULL)
			{
				enet_peer_disconnect_now(peer, 0);
				window.close();
			}

		}
		/* SFML draw calls */

		//window.clear(sf::Color::Green);
		//window.draw(avatar);
		window.draw(enemy);
		window.display();

		Sleep(5);  // windows.h
	}

	delete newPosition;
	enet_host_destroy(server);
	enet_host_destroy(client);
	atexit(enet_deinitialize);
	return 0;
}