#ifndef GAME_H
#define GAME_H

/*Prototypes*/

void cap_framerate( Uint32 starting_tick );
double get_delta();
void process( SDL_Renderer * renderer );
void input( int * running );
void print_sdl_error( const char * message, const char * sdl_error_message );
Segment * create_snake( Uint16 snake_len );
void move_snake( Segment * snake, double snake_angle, Uint16 snake_len, int grow );
Vector2 set_apple( Segment * snake, Uint16 snake_len );
int eat_apple( Segment * snake, Uint16 snake_len, Vector2 apple_pos );
int collisions( Segment * snake, Uint16 snake_len );
void restart( Segment * snake, Uint16 snake_len );

#endif /* GAME_H */
