#include "main.h"
#include "draw.h"
#include "game.h"

void draw( SDL_Renderer * renderer, SDL_Texture * image, SDL_Rect srcrect, SDL_Rect dstrect, double angle, SDL_Point center, SDL_RendererFlip flip ) {
    SDL_RenderCopyEx( renderer, image, &srcrect, &dstrect, angle, &center, flip );
}

void draw_tile( SDL_Renderer * renderer, SDL_Texture * image, Vector2 pos ) {
    SDL_Rect srcrect;
    SDL_Rect dstrect;

    srcrect.x = 0; srcrect.y = 0; srcrect.w = 8; srcrect.h = 8;
    dstrect.x = pos.x * 8; dstrect.y = pos.y * 8; dstrect.w = 8; dstrect.h = 8;

    SDL_RenderCopy( renderer, image, &srcrect, &dstrect );
}

void draw_ground( SDL_Renderer * renderer, SDL_Texture * image ) {
    Uint8 x, y;
    Vector2 pos;

    for ( x = 0; x < WIN_WIDTH / 8; x++ ) {
        for ( y = 0; y < WIN_HEIGHT / 8; y++ ) {
            pos.x = x;
            pos.y = y;
            draw_tile( renderer, image, pos );
        }
    }
}

SDL_Texture * load_texture( SDL_Renderer * renderer, char * path ) {
    SDL_Texture * image;

    image = IMG_LoadTexture( renderer, path );

    if ( image == NULL ) {
        // printf( "Cannot load texture: %s SDL_Error: %s\n", path, SDL_GetError() );
        print_sdl_error( "Cannot load texture", SDL_GetError() );
        return image;
    }
    else {
        return image;
    }
}
