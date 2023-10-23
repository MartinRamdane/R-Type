# R-Type Engine

Here you can find out how to create your own game and how our Engine works.

# The Engine

The engine works with a Core, Entity and EntityType.

## The Core

In the Core, all you have to do is replace "Game" with your own game class.
`_game  =  std::make_shared<Game>(_engine);`

## The principals classes

To create your game, you can use already-created classes such as **StaticObject** for objects with no life or interest, **Character** for living entities with life, speed or even a fire rate if required.
You can also create your own classes by inheriting our **IEntity** interface.

## The IGame Interface

To create your own game, your **Game** class must inherit from the **IGame** interface.
The only function you need to implement is the update.
`virtual  void  update(std::vector<ACTION> actions) =  0;`
This function takes as parameters the actions requested by the client that you need to execute.
For more information on these **ACTION**, please refer to the server documentation.
[server.md](server.md)

## Your Game

To create your game, you need to create a folder with the name of your game in the engine folder:
**src/engine/nameOfYourGame**
In this folder you can create all the classes you need, as well as your **Game** class.

# The Game class

Your class must inherit the **IGame** interface, but here's what else you can implement to make your code more practical:

-   Create groups of entities like that.

    > `std::shared_ptr<EntityType<IEntity>>  _playersGroups;`

    You need to give the radius of the **EntityType**:

    > `_playersGroups  =  std::make_shared<EntityType<IEntity>>(16);`

-   Create an instance of your game in you **Game.hpp**. And initiate it in the constructor.
    > `static  Game  *instance;` > `instance  =  this;`
-   Create a relationship between groups of entities to automatically manage collisions. To do this create a pointer to the Engine and take it in the constructor of the game.

    > `std::shared_ptr<Engine>  _engine;` > `Game::Game(std::shared_ptr<Engine>  &engine) : _engine(engine)`

    To set the relation juste use `setRelation`, the first parameter is the first group, the second is the second group and the last parameter is the function to call when there is a collision.

    > `engine->setRelation(_projectilesGroups, _orangeRobotGroups, Projectile::hurtEntity);`

    It must be static and have this definition:

    > `static  void  hurtEntity(IEntity  &self, IEntity  &you);`

## Json configuration

To configure your game and sprites behavior like the game assets, sprite positions, etc., you are going to use a Json file. There is a **JsonParser class** that is responsible for parsing the Json file. This class uses a builtin library called **JSON for Modern C++**.
Here is the link to the library doc: https://github.com/nlohmann/json

**IMPORTANT:** The parser searches recursively for your file starting from the root directory, so name your files correctly so you don't have two with the same name

Along with the ones I'll list below, the other files do not have a specific way or rule to follow. It is up to you to decide the structure and informations that you are goint to put on it!

-   WindowConfig.json is used to config the screen size and name.
-   rTypeAnimationConfig.json _(you must create one for each game)_ is how the sprite's behavior should be handled in the graphical display. When creating a sprite using the `ecreate` protocol, you must specify the name of the file containig the sprites config and also the object that will be used to do the sprite animation:
    `return ... entity->getSpriteJsonFileName() " " + entity->getSpriteConfigJsonObjectName() ...`

Taking a look into the rTypeAnimationConfig.json file, you will find this:

    ...
    "Enemy1":
    {
    	"nb_rect": "2",
    	"rect_init": "0",
    	"form": "loop"
    }
    ...

    - nb_rect: number of animations that make up the sprite
    - rect_init: in which rect the animations starts
    - form: the animation type (loop, once, event...)

The following files are examples:

-   rTypeSetup.json is used to load all the game assets
-   rTypeLevels.json is used to create the game levels, the sprites, their amout, positions, speed, fire rate and all other informations that are necessary for your game to run.

The two files mentioned above are specific to each game and the way the information contained in them is managed and parsed can be structured any way you like!
