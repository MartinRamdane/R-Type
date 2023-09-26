# R-Type API

We have 2 different types of API based on TCP and UDP server.

## TCP API

The TCP API is used for the TCP Connection between a Client and a Server Instance.

The Server Instances represent the lobbies.

The structure of TCP API is like this:
> ACTION ACTION_NAME;
int body_size;
char *body;

The ACTION_NAME is the target action of the event representing by this enum :

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

*e.g :*
client send -> `JOIN, 4, 1 1 (JOIN, size_t, instance_id player_id)`
server send -> `JOINED, 4, 1 1 (JOINED, size_t, instance_id player_id)`

## UDP API

The UDP API is used for the UDP Connection when the client is connected to an instance.

UDP Server is in the asio thread and linked to the Game Engine.

The server MUST send a sprite list to the client that should display all sprites of the list.

// voir avec ADAM

We have some requests for the Client to the Server.
It correspond to the main player actions.

The structure of this request is like TCP API :
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