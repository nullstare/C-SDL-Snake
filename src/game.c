#include "main.h"
#include "game.h"
#include "draw.h"

void process( SDL_Renderer * renderer ) {
    Uint32 starting_tick;
    int running = 1;

    SDL_Texture * grass_tex = load_texture( renderer, "img/grass.png" );
    SDL_Texture * apple_tex = load_texture( renderer, "img/apple.png" );

    /* Randomize */
    // time_t t;
    // srand( (unsigned) time(&t) );
    srand( time(0) );

    /*apple test*/
    Vector2 pos;
    pos.x = rand() % ( WIN_WIDTH / 8 );
    pos.y = rand() % ( WIN_HEIGHT / 8 );

    // printf( "%d\n", pos.x);

    while ( running ) {
        starting_tick = SDL_GetTicks();
        running = input();
        draw_ground( renderer, grass_tex );
        draw_tile( renderer, apple_tex, pos );
        
        SDL_RenderPresent( renderer );
        cap_fps( starting_tick );
    }
    // return starting_tick;
}

void cap_fps( Uint32 starting_tick ) {
    Uint32 frame_ticks = SDL_GetTicks() - starting_tick;

    if ( ( 1000 / FPS ) > frame_ticks ) {
        SDL_Delay( 1000 / FPS - frame_ticks );
    }
}

int input() {
    SDL_Event event;

    if ( SDL_PollEvent( &event ) ) {
        if ( event.type == SDL_QUIT ) {
            return 0;
        }
    }
    return 1;
}

void print_sdl_error( char * message, const char * sdl_error_message ) {
    printf( "%s. SDL_Error: %s\n", message, sdl_error_message );
}
