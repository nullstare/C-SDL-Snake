#ifndef DRAW_H
#define DRAW_H

/*Prototypes*/

SDL_Texture * load_texture( SDL_Renderer * renderer, char * path );
void draw( SDL_Renderer * renderer, SDL_Texture * image, SDL_Rect srcrect, SDL_Rect dstrect, double angle, SDL_Point center, SDL_RendererFlip flip );
void draw_tile( SDL_Renderer * renderer, SDL_Texture * image, Vector2 pos );
void draw_ground( SDL_Renderer * renderer, SDL_Texture * image );

#endif /* DRAW_H */
