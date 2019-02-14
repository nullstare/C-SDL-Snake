# About
Simple Snake game using SDL2. I made this mostly as a coding exercise some time ago so don't expect anything groundbreaking :smiley:. Some parts could potentially be used for other simple games.

# Make
Compilation on UNIX like systems.

Debendencies:
```
sdl2
sdl2_image
```
Go to game folder and type
```
make
```
You should now have **Snake** executable in the folder.

If you get error about "-no-pie" remove it from LFLAGS in Makefile.

# Controls
**Arrows** to turn, **Escape** to quit and **Enter** to start new game when dead.
