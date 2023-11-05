The project is available on 3 platforms (Linux, Windows & MacOS).

# Prerequisites

## Linux

* You need to [install conan2](https://docs.conan.io/2/installation.html) using python or your preferred package manager.
* You need to have gcc, g++ and cmake installed.

## Windows

**Our project has been developped and tested on Windows using cl (MSVC) not MinGW. You can try to use MinGW but it hasn't been tested. Theses instructions are for MSVC ONLY.**
***

* You need to [install conan2](https://docs.conan.io/2/installation.html) using [chocolatey](https://community.chocolatey.org/packages/conan) or python.
* You need to have MSVC **(2022)** installed and ready-to-use (you can see if it's available by typing ```cl --version``` on any terminal).
* You need to have [cmake installed](https://community.chocolatey.org/packages/cmake).

## MacOS

* You need to [install conan2](https://docs.conan.io/2/installation.html) using python or your preferred package manager.
* You need to have clang and cmake installed.


# Installing

If you haven't created a conan profile yet, use ```conan profile detect --force```

At the root of the repository you can now use ```conan install . --output-folder=build --build=missing``` to generate the build/ folder and install our dependencies. 

## Disabling compilation

You can disable the compilation of some part of our project using CMAKE flags.

You can disable the compilation of the client using ```-DBUILD_CLIENT=OFF```

You can disable the compilation of the server using ```-DBUILD_SERVER=OFF```

You can disable the compilation of the editor using ```-DBUILD_EDITOR=OFF```

You can disable the compilation of the tests using ```-DBUILD_TESTS=OFF```


## Windows

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

Then for both modes : 

`cmake --build .`

# Executing

The binaries will be generated at the root of the repository.

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