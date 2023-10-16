
# Client

The Client is the player's program.
It connects to the server, creates/joins a game instance and displays the game.

# How it work ?

The customer section is divided into 3 parts:
- Game display
- Managing connections/communication with the server
- Parser

# Game display

Folder: src/client
Important Files: Game, Entity, RessourcesManager, Login, Menu

The SFML lib is used to display the game.
The **Game** class handles SFML management.

The main loop is handle by the `Game.run()` function.
If you want to add other events you have to go in the `Game.handleEvent()` function.
For drawing element we use the `Game.update()` function.

It retrieves the information sent by the parser and creates a map of class **Entity**.
This map contains all the Sprites and their Id to be displayed during the game.
The client receive a `tuple<int, Entity>` of the **Parser**.

In the `Game.addEntity()` function who is taking the Tuple in argument,
the Client is checking if the Entity is existing using the Id in the tuple.
{
    if (findEntity(id) == true)
    {
        _entities[id].setNextPos(entity.getNextPos());
    }
    else
        _entities[id] = entity;
}
if the entity exists, the client only modifies its coordinates using those of the entity passed in the tuple,
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
