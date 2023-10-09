# R-Type API

We have 2 different types of API based on TCP and UCP server.

## TCP API

The TCP API is used for the TCP Connection between a Client and an Server Instance.

The Server Instances represent the lobbies.

The structure of TCP API is like this:
> ACTION ACTION_NAME;
int body_size;
char *body;

The ACTION_NAME is the target action of the event representing by this enum:

> enum  ACTION
> {
	OK,
	KO,
	CONNECT,
	CREATE,
	LIST,
	JOIN,
	JOINED,
	READY,
	START
};

It's only for the connection of the Client to the Instance.

body_size represents the size of the char *event which contains the value of the request.

*e.g:*
client send -> `JOIN, 4, 1 1 (JOIN, size_t, instance_id player_id)`
server send -> `JOINED, 4, 1 1 (JOINED, size_t, instance_id player_id)`

## UDP API

The UDP API is used for the UDP Connection when the client is connected to an instance.

UDP Server is in the asio thread and linked to the Game Engine.

The server MUST send a sprite list to the client that should display all sprites of the list.

For this, use the `SPRITE` event.

We have some requests for the Client to the Server.
It correspond to the main player actions.

The structure of this request is like TCP API:
> EVENT EVENT_NAME;
int body_size;
char *body;

The EVENT_NAME corresponds to the target action of the player.

> enum  EVENT
> {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	SHOOT,
	QUIT,
};

> EVENT body_size body\n;

The mention "\n" at the end of the UDP request guarantees that it has been received in its entirety.

Event requests only concern the client; the server does not have to reply to the client if the event has been received or if it has succeeded.

### Events

#### TCP Requests

|Client|Server OK|Server KO|Info|
|---|---|---|---|
|CONNECT, playerNameSize, "playerName"|OK, 9,<br> "Connected"|KO, 18,<br> "Connection refused"| TCP Client try to connect to TCP Server |
|CREATE, 0, ""|OK, size,<br> "instancePort instanceId"|KO, 21,<br> "Can't create instance"|Client try to create a lobby|
|---|LIST, size,<br> "{instanceName, instanceId, nbPlayers}[]"|---|Send to Client all created Instances|

#### UDP Requests

##### Connection
To assure the connection between the UDP Server and the Client, we've implemented 2 special events for that: Ping and Pong.
The Server should sent `PING` event and the Client answer with a `PONG` event.

`PING, 0, ""`
`PONG, 0, ""`

So, the Client is disconnected from the UDP Server if it hasn't received a `PONG` event after 3 `PING` event have been sent.

|Client|Server OK|Server KO|Info|
|---|---|---|---|
|JOIN, 2, "ok"|JOINED, size, "windowTitle windowWidth windowHeight"|JOINED, 2, "ko"|Client try to join the instance|
|---|SPRITE, size, "entityId x y entitySprite rotation scaleX scaleY jsonConfigFilePath entityType"|---|Server send to the client sprite informations|
