#ifndef MAIN_H
#define MAIN_H

#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
// #include <stdio.h>

#define WIN_WIDTH 128
#define WIN_HEIGHT 128
#define FPS 60

/*Prototypes*/

void game_window();

/*Structs*/

typedef struct {
    int32_t x;
    int32_t y;
} Vector2;

#endif /* MAIN_H */
