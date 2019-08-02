# About
Simple Snake game using SDL2. I made this mostly as a coding exercise some time ago so don't expect anything groundbreaking :smiley:. Some parts could potentially be used for other simple games.

# Build
Compilation on UNIX like systems.

Dependencies:
```
sdl2
sdl2_image
```
Install packages on Ubuntu:
```
sudo apt install libsdl2-dev
sudo apt install libsdl2-image-dev
```
Go to game folder and type
```
cd build
cmake ..
make
./Snake
```
You should now have **Snake** executable in the build folder.

# Controls
**Arrows** to turn, **Escape** to quit and **Enter** to start new game when dead.
