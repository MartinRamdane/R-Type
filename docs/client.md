
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
The Game class handles SFML management.
It retrieves the information sent by the parser and creates a map of class Entity.
This map contains all the Sprites and their Id to be displayed during the game .

# Managing connexion/communication

Folder: src/client
Important Files: TCPClient, UDPClient, ThreadPool

In the Game class, the communication with the Server is handle.
All commands are converted to binary and sent to the UDP Server.
Commands are sent when the player performs an action.
The commands received correspond to the display of all entities present in the game.
All their information (position, status, etc.) is continuously sent to the client.

# Parser

Folder: src/client
Important File: Parser

The parser retrieves the command sent by the server and
creates the Entities according to the information received.
The Entities created are sent to the Game class and added to the map.