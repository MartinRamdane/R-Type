# Request

## Legend

X - Width position value
Y - Height position value
n - user id
i - entity id
b - bonus id
s - score (int)
? - the response can be true of false (901 or 902)
... - no request

Requests beginning with 'p' correspond to player informations or actions
Requests beginning with 'e' correspond to entity informations or actions (like ennemies, bonus, barriers...).

### User
|Server| Client | Info|
|--|--|--|
|pup n X Y\n|pup n\n  |the player N is going up |
|pdown n X Y\n|pdown n\n  |the player N is going down |
|pleft n X Y\n|pleft n\n  |the player N is going left |
|pright n X Y\n|pright n\n  |the player N is going right |
|?|pinteract n\n  |the player N has pressed the interact input |
|?|pmenu n\n  |the player N has pressed the menu input |
|pbonus n b\n|...|the player N get the bonus B |

### Game
|Server| Client | Info|
|--|--|--|
|dead n\n|...|the player N is dead|
|score n s\n|...|the player N's score|

### Entities
|Server| Client | Info|
|--|--|--|
|emove i X Y\n|...|the entity I is moving|
|edead i\n|...|the entity I is dead or destroyed|

Table ronde ©