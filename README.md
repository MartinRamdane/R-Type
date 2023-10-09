
# R-TYPE

Main C++ project in 3rd year at Epitech.
The R-TYPE is a mutliplayer game based on existing R-Type game.

The project is split in 3 parts:

 - Client side
 - Server side (in UDP and TCP protocol)
 - Game Engine

## Docs

For the Server API Reference, we've created an API doc in docs folder.

[server.md](/docs/server.md)

For the Client documentation:

[client.md](/docs/client.md)

For the Game Engine documentation:

[gameEngine.md](/docs/gameEngine.md)

## Installation

First, you must install conan:

```pip install conan```

or if you have a different OS [go here](https://conan.io/downloads)

After this clone this project and do this :

```conan profile detect --force``` to create your conan profile

```conan install . --output-folder=build --build=missing``` to install all dependencies

For windows :

    cd build
    cmake ..
    cmake --build . --config Debug

For mac and linux :

    cd build
    cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release // For the first compilation
    cmake .. // If you've already compiled
    cmake --build .


## Authors

- [@fgrimaepitech](https://github.com/fgrimaepitech) Server side
- [@adamlbs](https://github.com/AdamLBS) Server side
- [@gabrielmorais](https://github.com/gabrielmorais4) Game Engine side
- [@martinramdane](https://github.com/MartinRamdane) Game Engine side
- [@luluri](https://github.com/Luluri) Client side



