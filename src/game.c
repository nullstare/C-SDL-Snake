#include "main.h"
#include "game.h"
#include "draw.h"

void process( SDL_Renderer * renderer ) {
    Uint32 starting_tick;
    int running = 1;

    SDL_Texture * grass_tex = load_texture( renderer, "img/grass.png" );
    SDL_Texture * apple_tex = load_texture( renderer, "img/apple.png" );
    SDL_Texture * snake_tex = load_texture( renderer, "img/snake.png" );

    /* Randomize */
    srand( time(0) );

    /*apple test*/
    Vector2 pos;
    pos.x = rand() % ( WIN_WIDTH / 8 );
    pos.y = rand() % ( WIN_HEIGHT / 8 );

    Uint16 snake_len = 3;
    Segment * snake = create_snake( snake_len );

    while ( running ) {
        starting_tick = SDL_GetTicks();
        running = input();
        draw_ground( renderer, grass_tex );
        draw_tile( renderer, apple_tex, pos );
        draw_snake( renderer, snake_tex, snake, snake_len );

        SDL_RenderPresent( renderer );
        cap_fps( starting_tick );
    }

    free( snake );
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

void print_sdl_error( const char * message, const char * sdl_error_message ) {
    printf( "%s. SDL_Error: %s\n", message, sdl_error_message );
}

Segment * create_snake( Uint16 snake_len ) {
    Segment * snake;
    Uint8 i;
    Vector2 map_tile_size;

    map_tile_size.x = WIN_WIDTH / 8;
    map_tile_size.y = WIN_HEIGHT / 8;

    /*Snake can be the size of the playfield*/
    // snake = (Segment*) malloc( ( ( WIN_WIDTH / 8 ) * ( WIN_HEIGHT / 8 ) ) * sizeof( Segment ) );
    snake = (Segment*) malloc( map_tile_size.x * map_tile_size.y * sizeof( Segment ) );
    // snake = (Segment*) malloc( ( 16 * 16 ) * sizeof( Segment ) );

    if ( snake == NULL ) {
        printf( "Not able to allocate memory for snake!\n" );
    }

    for ( i = 0; i < snake_len; i++) {
        snake[i].pos.x = map_tile_size.x / 2 - i;
        snake[i].pos.y = map_tile_size.y / 2;
        snake[i].angle = 0;
    }

    return snake;
}
