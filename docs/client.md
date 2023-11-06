
# Client

The Client is the player's program.
It connects to the server, creates/joins a game instance and displays the game.

# How it work ?

The customer section is divided into 3 parts:
- Game display
- Managing connections/communication with the server
- Parser

# Game display

Folder: src/client and src/client/SFML
Important Files: Game, IDisplay, DisplaySFML, IEntity, EntitySFML, RessourcesManager, Login, Menu

The SFML lib is used to display the game.
There is a **IDisplay** class and a child class named **DisplaySFML** that handle all the fucntion for displaying the game
If you want to add another graphic lib you can create a new **Display** class that inherit from **IDsiplay**.
It's the same thing for the entities handling, there is a **IEntity** class and a **EntitySFML** class to create and manage game entities.
So you have to create a new **Entity** class if you add a new graphic lib.
We can aslo use the SDL lib and for that all the class named with SFML are existing with SDL.

The main loop is handle by the `Game.run()` function.
All the entities are display in the draw function of the **DisplaySFML** class.
The event actions are manage in the `handleEvent()` function in the **Display** class. this function return a string corresponding to the event like this.
```
if (std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now() - _lastFrameTime)
            .count() > 10) {
        _lastFrameTime = std::chrono::high_resolution_clock::now();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            _events.push_back("left");
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            _events.push_back("right");
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            _events.push_back("up");
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            _events.push_back("down");
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            _events.push_back("space");
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            _events.push_back("s");
```
and in the **Game** class the function `getEvent` is doing a action for each event like this 
```
std::vector<std::string> events = _display->getEvents();
    Event evt;
    std::string playerId = "p" + std::to_string(_playerId);
    for (auto event : events) {
        if (event == "close")
            _client->Disconnect();
        if (event == "r")
            evt.ACTION_NAME = ACTION::FLIP;
        if (event == "left")
            evt.ACTION_NAME = ACTION::LEFT;
        if (event == "right")
            evt.ACTION_NAME = ACTION::RIGHT;
        if (event == "up")
            evt.ACTION_NAME = ACTION::UP;
        if (event == "down")
            evt.ACTION_NAME = ACTION::DOWN;
        if (event == "space")
            evt.ACTION_NAME = ACTION::SPACE;
        if (event == "s")
            evt.ACTION_NAME = ACTION::KEY_S;
        evt.body = playerId;
        _udpClient->sendEvent(evt);
    }
```
So if you want to add action and event you have to modify this 2 functions.

It retrieves the information sent by the parser and creates a map of class **IEntity**.
This map contains all the Sprites and their Id to be displayed during the game.
The client receive a `tuple<int, EntityInfos>` of the **Parser** and with this tuple the **DisplaySFML** create the entity and stock here in a map.
If the entity exists, the client only modifies its coordinates or is state using those of the entity passed in the tuple,
otherwise it creates a new entity and stores it in the map.

When the Entity is create, we use a **RessourceManager** class who is loading all the texture using in SFML at the start of the program for reducing the lag of the game.

# Managing connexion/communication

Folder: src/client
Important Files: TCPClient, UDPClient, ThreadPool

In the **Game** class, the communication with the Server is handle.
All commands are converted to binary and sent to the UDP Server.
Commands are sent when the player performs an action.
The commands received correspond to the display of all entities present in the game.
All their information (position, status, etc.) is continuously sent to the client.

# Parser

Folder: src/client
Important File: Parser

The parser retrieves the command sent by the server and
creates the Entities according to the information received.
The Entities created are sent to the **Game** class and added to the map.

You have to use the `Parser.parseMessage()` function that take a string in argument.
The string is the command translate from the binary send by the server.
We use a protocol:
    - `ecreate id pos.x pos.y path rotaion scale.x scale.y configPath objectType`
        > this command call the `Paser.addEntity()` function who is creating a new **Entity** and send it to the **Client**
    - `emove id newPos.x newPos.y`
        > this command call the `Parser.moveEntity()` function whos is modifying the position of an **Entity**
    - `dead id`
        > this command inform the Client that the Entity is dead
All the command return a `tuple<int, Entity>` with the new Entity and here ID

# Arguments of protocol

- id (int) : It's the id of the entity
- pos.x (float) and pos.y (float) : It's the position X and the position Y of the **Entity** at the start
- path (string) : It's the path for loading the texture of the **Entity** sprite
- rotation (int) : It's the angle of sprite's rotation, 0 by default
- scale.x (float) and scale.y (float) : It's the scale number for the sprite, 1 by default
- configPath (string) : It's the path for the config file for setting the animation of each **Entity**
- objectType (string) : It's the type of the **Entity** use in the configFile
