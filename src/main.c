#include "main.h"
#include "game.h"

int main(int argc, char const **argv) {
    game_window();

    return 0;
}

void game_window() {
    SDL_Window *window;

    // printf("sign of 2 is %d\n", SIGN(2));
    // printf("sign of -5 is %d\n", SIGN(-5));

    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        print_sdl_error( "Unable to initialize SDL video", SDL_GetError() );
    }
    window = SDL_CreateWindow(
        "Snake",
        SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
        WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_RESIZABLE );

    if ( window == NULL ) {
        print_sdl_error( "Error in creating window", SDL_GetError() );
    }

    SDL_Renderer *renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    /* Other SDL settings */
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "0" );
    SDL_RenderSetLogicalSize( renderer, WIN_WIDTH, WIN_HEIGHT );

    if ( renderer == NULL ) {
        print_sdl_error( "Error in creating renderer", SDL_GetError() );
    }

    SDL_Surface * icon = IMG_Load( "img/apple.png" );
    SDL_SetWindowIcon( window, icon );

    process( renderer );

    SDL_DestroyWindow( window );
    SDL_Quit();
}
