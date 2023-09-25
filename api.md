# Request

All requests are sent and received in binary protocol.
Example :

> Encoded data: 42 0 0 0 112 117 112 32 49 32 49 48 32 50 48 10
> Decoded data: pup 1 10 20

So you only see the decoded values of the queries.

## Legend

X - Width position value
Y - Height position value
r - Rotation value
asset - path of sprite
n - user id
i - entity id
b - bonus id
s - score (int)
? - not mandatory
... - no request

Requests beginning with 'p' correspond to player informations or actions
Requests beginning with 'e' correspond to entity informations or actions (like ennemies, bonus, barriers...).

### User
|Server| Client | Info|
|--|--|--|
|...|pup n\n  |the player N is going up |
|...|pdown n\n  |the player N is going down |
|...|pleft n\n  |the player N is going left |
|...|pright n\n  |the player N is going right |
|pmove n X Y\n|...|the player N is moving |
|901/902|pinteract n\n  |the player N has pressed the interact input |
|901/902|pmenu n\n  |the player N has pressed the menu input |
|pbonus n b\n|...|the player N get the bonus B |

### Game
|Server| Client | Info|
|--|--|--|
|create n\n|...|the player N creates a new instance|
|join id_instance\n|...|the player N joins an instance|
|dead n\n|...|the player N is dead|
|score n s\n|...|the player N's score|

### Entities
|Server| Client | Info|
|--|--|--|
|ecreate i X Y asset rotation? scale?\n|...|create an entity with ID, X and Y positions, the sprite path, the rotation and scale|
|epos i X Y\n|epos i\n|send the entity I's position|
|emove i X Y\n|...|send the new entity's position|
|edead i\n|...|the entity I is dead or destroyed|

Table ronde ©