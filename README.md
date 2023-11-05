
# R-TYPE

Main C++ project in 3rd year at Epitech.
The R-TYPE is a mutliplayer game based on existing R-Type game.

## Project parts
The project is split in 3 parts :
 - Client side
 - Server side (in UDP and TCP protocol)
 - Game Engine

<img width="949" alt="CleanShot 2023-10-09 at 11 05 40@2x" src="https://github.com/EpitechPromo2026/B-CPP-500-MAR-5-1-rtype-martin.ramdane/assets/91624379/0e3d18fb-7132-4f78-a555-86ab2678dd3e">

### Client side
The Client is the player's program. It connects to the server, creates/joins a game instance and displays the game. It is itself divided into 3 parts : 
* Game display
* Managing connections/communication with the server
* Parsing data received from the server
### Server side (networking)
The server is the program that manages networking and handle data received / sent from/to the client. It uses an RFC specially made for the R-TYPE. The server also interacts with the game engine.
### Game Engine
The Game Engine is the core of the R-TYPE. It manages the game and the entity associated to each game.

## How can I learn more about each part ? 

You can learn more about each part using the sections in our wiki

* [Client documentation](https://github.com/EpitechPromo2026/B-CPP-500-MAR-5-1-rtype-martin.ramdane/wiki/Client-documentation)
* [Server documentation](https://github.com/EpitechPromo2026/B-CPP-500-MAR-5-1-rtype-martin.ramdane/wiki/Server-documentation)
* [Game Engine Documentation](https://github.com/EpitechPromo2026/B-CPP-500-MAR-5-1-rtype-martin.ramdane/wiki/Game-Engine-documentation)

## Documentation

You can find documentation regarding our project in the [wiki](https://github.com/EpitechPromo2026/B-CPP-500-MAR-5-1-rtype-martin.ramdane/wiki)

## Installation

### Prerequisites

For the installation, you can use the package manager you want.

But for a simple installation, we suggest you to use Conan.

You need to [install conan2](https://docs.conan.io/2/installation.html) using python or your preferred package manager.
You need to have a C++ compiler like Cmake, Clang...

If you haven't created a conan profile yet, use ```conan profile detect --force```

At the root of the repository you can now use ```conan install . --output-folder=build --build=missing``` to generate the build/ folder and install our dependencies.

### Windows

For Windows, in order to generate the executables you need to execute theses commands in the **build folder** : 

`cmake ..`
***
Depending on your Release mode you need to specify if you're in Debug or Release mode (it is specified in your conan profile).
***
### Release mode
`cmake --build . --config Release`

### Debug mode
`cmake --build . --config Debug`

## UNIX (MacOS / Linux)

For UNIX-based systems in order to generate the executables you need to execute theses commands in the **build folder** :
***
Depending on your Release mode you need to specify if you're in Debug or Release mode (it is specified in your conan profile).
***
### Release mode
`cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release`

### Debug mode
`cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug`

You can find details on the installation here [wiki](https://github.com/EpitechPromo2026/B-CPP-500-MAR-5-1-rtype-martin.ramdane/wiki/Installation)

## Docker

You can also use Docker to build the project. Two Dockerfile and a docker-compose.yml are available at the root of the repository.

You can also use our compiler image available on Docker Hub [here](https://hub.docker.com/r/adamelm/r-type-compiler) to build the project.
This image contains all the dependencies needed to build the project and is based on ubuntu:latest

### Build the project with Docker

You can directly use the Dockerfile at the root of the repository to build the project.

You can use the following commands to build the project :

`docker build -t r-type .\Dockerfile.build`

### Build and run the server with Docker

You can use docker compose to build and run the server.

Simply use the following command at the root of the repository :

`docker-compose up`

## Executing

### Release mode

You will have a "Release/" folder at the root of the repository with 2 .exe files : 
* r-type_client.exe
* r-type_server.exe
You can then execute theses files with ```./r-type_client.exe``` or ```./r-type_server.exe``` 

### Debug mode

You will have a "Debug/" folder at the root of the repository with 2 .exe files : 
* r-type_client.exe
* r-type_server.exe
You can then execute theses files with ```./r-type_client.exe``` or ```./r-type_server.exe``` 

## Releases

All releases are available [here](https://github.com/EpitechPromo2026/B-CPP-500-MAR-5-1-rtype-martin.ramdane/releases)

## Authors

- [@fgrimaepitech](https://github.com/fgrimaepitech) Server side
- [@adamlbs](https://github.com/AdamLBS) Server side
- [@gabrielmorais](https://github.com/gabrielmorais4) Game Engine side
- [@martinramdane](https://github.com/MartinRamdane) Game Engine side
- [@luluri](https://github.com/Luluri) Client side



