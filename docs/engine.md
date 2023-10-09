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

- Create groups of entities like that.
	> `std::shared_ptr<EntityType<IEntity>>  _playersGroups;`

	You need to give the radius of the **EntityType**:
	> `_playersGroups  =  std::make_shared<EntityType<IEntity>>(16);`

- Create an instance of your game in you **Game.hpp**. And initiate it in the constructor.
	> `static  Game  *instance;`
	> `instance  =  this;`
	
- Create a relationship between groups of entities to automatically manage collisions. To do this create a pointer to the Engine and take it in the constructor of the game.
	> `std::shared_ptr<Engine>  _engine;`
	> `Game::Game(std::shared_ptr<Engine>  &engine) : _engine(engine)`
	
	To set the relation juste use `setRelation`, the first parameter is the first group, the second is the second group and the last parameter is the function to call when there is a collision.
	> `engine->setRelation(_projectilesGroups, _enemiesGroups, Projectile::hurtEntity);`

	It must be static and have this definition:
	> `static  void  hurtEntity(IEntity  &self, IEntity  &you);`

## Json configuration
 [@gabrielmorais](https://github.com/gabrielmorais4) To do