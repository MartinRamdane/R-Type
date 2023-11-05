# R-Type API

<img width="949" alt="CleanShot 2023-10-09 at 11 05 40@2x" src="https://github.com/EpitechPromo2026/B-CPP-500-MAR-5-1-rtype-martin.ramdane/assets/91624379/0e3d18fb-7132-4f78-a555-86ab2678dd3e">

We have 2 different types of API based on TCP and UCP server.

The TCP server is unique, and must manage all game instances.

Each game instance has its own game engine, depending on the game being run, and its own UDP server.

## Event Handler

We used an EventHandler class managing all events that can be sent between the Server and the Client.

This is the ACTION enum:
  * KO,
*   CONNECT,
*   CREATE,
*   LIST,
*   JOIN,
*   JOINED,
*   READY,
*   START,
*   LEFT,
*   RIGHT,
*   UP,
*   DOWN,
*   SPACE,
*   QUIT,
*   PING,
*   PONG,
*   SPRITE,
*   TEXT,
*   DEAD,
*   FLIP,
*   RESET,
*   UNKNOWN,
*   CHECK,
*   SOUND,
*   KEY

You can add new Action if you want.

Each event is compressed before being sent and decompressed when received. We used the lz4 library to compress and decompress the event body.

Also, each event is protected from corruption by a checksum. The checksum is calculated by the server when the event is sent, and the client checks that the checksum is correct when the event is received.

Full information about our RFC is available in the **rfc4242.txt** file inside of the **docs** folder.

An Event is composed by an ACTION and a body that is a string.

## TCP API

The TCP API is used for the TCP Connection between a Client and the Server.

The TCP server provides the connection between a client and the game server, and manages all interactions between a client and its connection to a game instance.

## TCP Requests

|Client|Server OK|Server KO|Info|
|---|---|---|---|
|CONNECT, "playerName"|OK, <br> "Connected"|KO, <br> "Connection refused"| TCP Client try to connect to TCP Server |
|CREATE, ""|OK, <br> "instancePort instanceId"|KO, 21,<br> "Can't create instance"|Client try to create a lobby|
|LIST, ""|LIST,<br>"{instanceName, instanceId, nbPlayers, maxPlayers}[]"|---|Send to Client all created Instances|
|JOIN, "instancePort playerId"|JOINED,<br>"instancePort playerId"|---|Client try to join an Instance (even if he's creating it)|

## UDP API

The UDP API is used to send all game information between the Client and the Game Instance server.

## UDP Requests

|Client|Server OK|Server KO|Info|
|---|---|---|---|
|READY, "playerId"|START, ""|---|The client has joined the instance then he's ready to receive all game information|
|---|SPRITE, "entityId x y entitySprite rotation scaleX scaleY jsonConfigFilePath entityType"|---|Server send to the client sprite information|
|KEY, "keyValue playerId"|---|---|The client send a key he has pressed|
|UP/DOWN/LEFT/RIGHT, "playerId"|---|---|Moving the player, you can use KEY instead of|
|---|DEAD, "entityId"|---|This entity is destroyed|
|---|SOUND, "soundId"|---|To play a sound|
|---|TEXT, "textValue + spriteInformation"|---|To show a Text|

You have other events such as SPACE, RESET... In general, when a client sends a user input, it must specify the player ID in the body of the event.
