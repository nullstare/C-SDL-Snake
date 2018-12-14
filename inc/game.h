#ifndef GAME_H
#define GAME_H

/*Prototypes*/

void cap_fps( Uint32 starting_tick );
double get_delta();
void process( SDL_Renderer * renderer );
int input();
void print_sdl_error( char * message, const char * sdl_error_message );

#endif /* GAME_H */
