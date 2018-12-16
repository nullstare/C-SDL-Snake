#include "main.h"
#include "game.h"
#include "draw.h"

void process( SDL_Renderer * renderer ) {
    Uint32 starting_tick;
    int running = 1, eaten = 0, can_turn = 1, grow = 0, alive = 1;

    /*Textures*/
    SDL_Texture * grass_tex = load_texture( renderer, "img/grass.png" );
    SDL_Texture * apple_tex = load_texture( renderer, "img/apple.png" );
    SDL_Texture * snake_tex = load_texture( renderer, "img/snake.png" );

    /* Randomize */
    srand( time(0) );

    /*Snake variables*/
    Uint16 snake_len = 3;
    Segment * snake = create_snake( snake_len );
    /*Timing*/
    Uint64 old_time, new_time = SDL_GetPerformanceCounter();
    const double game_speed = 0.15;
    double delta, game_time_current = 0.0, steer_angle = 0.0;

    /*apple set pos*/
    Vector2 apple_pos;
    apple_pos = set_apple( snake, snake_len );

    while ( running ) {
        starting_tick = SDL_GetTicks();
        old_time = new_time;
        new_time = SDL_GetPerformanceCounter();
        delta = (double)( ( new_time - old_time ) / (double)SDL_GetPerformanceFrequency() );
        game_time_current += delta;

        if ( can_turn ) {
            input( &running, &steer_angle );
            can_turn = 0;

            if ( running == 2) {
                snake_len = 3;
                restart( snake, snake_len );
                running = 1;
                apple_pos = set_apple( snake, snake_len );
                alive = 1;
                steer_angle = 0.0;
            }
        }

        if ( alive && game_time_current >= game_speed ) {
            move_snake( snake, steer_angle, snake_len, grow );
            grow = 0;

            alive = collisions( snake, snake_len );

            if ( eat_apple( snake, snake_len, apple_pos ) ) {
                apple_pos = set_apple( snake, snake_len );
                snake_len++;
                grow = 1;
            }
            can_turn = 1;
            game_time_current = 0.0;
        }

        if ( !alive && can_turn == 0 ) {
            /*Wont block inputs after death*/
            can_turn = 1;
        }

        draw_ground( renderer, grass_tex );
        draw_tile( renderer, apple_tex, apple_pos );
        draw_snake( renderer, snake_tex, snake, snake_len );
        SDL_RenderPresent( renderer );
        cap_framerate( starting_tick );
    }
    free( snake );
}

void cap_framerate( Uint32 starting_tick ) {
    Uint32 frame_ticks = SDL_GetTicks() - starting_tick;

    if ( ( 1000 / FPS ) > frame_ticks ) {
        SDL_Delay( 1000 / FPS - frame_ticks );
    }
}

void input( int * running, double * angle ) {
    SDL_Event event;

    while ( SDL_PollEvent( &event ) ) {
        switch ( event.type ) {
            case SDL_QUIT:
                *running = 0;
                return;
            case SDL_KEYDOWN:
                if ( event.key.keysym.sym == SDLK_RIGHT && *angle != 180.0) {
                    *angle = 0;
                    return;
                }
                else if ( event.key.keysym.sym == SDLK_LEFT && *angle != 0.0) {
                    *angle = 180.0;
                    return;
                }
                else if ( event.key.keysym.sym == SDLK_DOWN && *angle != 270.0) {
                    *angle = 90.0;
                    return;
                }
                else if ( event.key.keysym.sym == SDLK_UP && *angle != 90.0) {
                    *angle = 270.0;
                    return;
                }
                else if ( event.key.keysym.sym == SDLK_RETURN ) {
                    *running = 2;
                    return;
                }
                else if ( event.key.keysym.sym == SDLK_ESCAPE ) {
                    *running = 0;
                    return;
                }
        }
    }
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
    snake = (Segment*) malloc( map_tile_size.x * map_tile_size.y * sizeof( Segment ) );

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

void move_snake( Segment * snake, double steer_angle, Uint16 snake_len, int grow ) {
    Uint16 i;

    for ( i = snake_len; i > 0; i-- ) {
        snake[i] = snake[i - 1];
    }
    snake[0].pos.x += round( cos( steer_angle * ( PI / 180.0 ) ) );
    snake[0].pos.y += round( sin( steer_angle * ( PI / 180.0 ) ) );
    snake[0].angle = steer_angle;
    snake[snake_len - 1].angle = snake[snake_len - 2].angle;

    if ( grow ) {
        snake[snake_len] = snake[snake_len - 1];
        grow = 0;
    }
}

int eat_apple( Segment * snake, Uint16 snake_len, Vector2 apple_pos ) {
    if ( snake[0].pos.x == apple_pos.x && snake[0].pos.y == apple_pos.y ) {
        return 1;
    }
    return 0;
}

Vector2 set_apple( Segment * snake, Uint16 snake_len ) {
    Vector2 apple_pos;
    int search = 1;
    Uint8 i;

    while ( search ) {
        apple_pos.x = rand() % ( WIN_WIDTH / 8 );
        apple_pos.y = rand() % ( WIN_HEIGHT / 8 );
        search = 0;

        for ( i = 0; i < snake_len; i++ ) {
            if ( snake[i].pos.x == apple_pos.x && snake[i].pos.y == apple_pos.y ) {
                search = 1;
                break;
            }
        }
    }
    return apple_pos;
}

int collisions( Segment * snake, Uint16 snake_len ) {
    Uint16 i;

    /*Borders*/
    if ( snake[0].pos.x < 0 || snake[0].pos.x >= (WIN_WIDTH / 8) || snake[0].pos.y < 0 || snake[0].pos.y >= (WIN_HEIGHT / 8) ) {
        return 0;
    }
    /*Body*/
    for ( i = 1; i < snake_len; i++ ) {
        if ( snake[0].pos.x == snake[i].pos.x && snake[0].pos.y == snake[i].pos.y ) {
            return 0;
        }
    }
    return 1;
}

void restart( Segment * snake, Uint16 snake_len ) {
    free( snake );
    create_snake( snake_len );
}
