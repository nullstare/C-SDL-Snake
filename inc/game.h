#ifndef GAME_H
#define GAME_H

/*Prototypes*/

void cap_fps( Uint32 starting_tick );
double get_delta();
void process( SDL_Renderer * renderer );
int input();
void print_sdl_error( const char * message, const char * sdl_error_message );
Segment * create_snake( Uint16 snake_len );

#endif /* GAME_H */
