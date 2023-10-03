
# R-TYPE

Main C++ project in 3rd year at Epitech.
The R-TYPE is a mutliplayer game based on existing R-Type game.

The project is split in 3 parts:

 - Client side
 - Server side (in UDP and TCP protocol)
 - Game Engine
## API Reference

For the Server API Reference, we've created an API doc in docs folder.

[api.md](/docs/api.md)



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
    cmake ..
    cmake --build .


## Authors

- [@fgrimaepitech](https://github.com/fgrimaepitech)
- [@adamlbs](https://github.com/AdamLBS)

- [@gabrielmorais](https://github.com/gabrielmorais4)
- [@martinramdane](https://github.com/MartinRamdane)
- [@luluri](https://github.com/Luluri)



