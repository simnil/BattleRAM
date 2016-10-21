# BattleRAM

BattleRAM is a real-time strategy game I'm developing in my spare time. As developement moves further this text will be updated.

## Building

The requirements for building are:
- __CMake__
- __SDL2__

### Installing dependencies

Download and install the SDL2 development libraries for Visual C++ from the official website. Then create an environment variable called `SDL2` and point it to the root of the SDL2 installation.

### Building a solution on Windows

__Requires: Visual Studio 2015__ or newer

Git will ignore a directory called "build" so it is advisable to let CMake generate the solition from there. If inside the build directory, a Visual Studio solution can be generated with the command:

	cmake .. "Visual Studio 14 2015 Win64"


I'd like to give a shout out to Peter Hillerström (https://github.com/PetorSFZ), whose help has many times been invaluable.