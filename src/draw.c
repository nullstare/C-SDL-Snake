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

void draw_snake( SDL_Renderer * renderer, SDL_Texture * image, Segment * snake, Uint16 snake_len ) {
    int i;
    SDL_Rect srcrect;
    SDL_Rect dstrect;
    SDL_Point center;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    center.x = 4; center.y = 4;
    srcrect.x = 0; srcrect.y = 0; srcrect.w = 8; srcrect.h = 8;
    dstrect.x = 8; dstrect.y = 8; dstrect.w = 8; dstrect.h = 8;

    for ( i = snake_len - 1; i > -1; i-- ) {
        dstrect.x = snake[i].pos.x * 8;
        dstrect.y = snake[i].pos.y * 8;

        if ( i == 0 ) {
            srcrect.x = 24;
        }
        else if ( i == snake_len - 1 ) {
            srcrect.x = 8;
        }
        else if ( snake[i].angle != snake[i - 1].angle ) {
            srcrect.x = 0;
            double val = 180.0 / PI, ang_to_next;

            ang_to_next = snake[i].angle + atan2( snake[i - 1].pos.x - snake[i].pos.x, snake[i - 1].pos.y - snake[i].pos.y ) * val;

            if ( round(ang_to_next) == 180.0 ) {
                flip = SDL_FLIP_VERTICAL;
            }
            else {
                flip = SDL_FLIP_NONE;
            }
        }
        else {
            srcrect.x = 16;
        }
        draw( renderer, image, srcrect, dstrect, snake[i].angle, center, flip );
    }
}

SDL_Texture * load_texture( SDL_Renderer * renderer, char * path ) {
    SDL_Texture * image;

    image = IMG_LoadTexture( renderer, path );

    if ( image == NULL ) {
        print_sdl_error( "Cannot load texture", SDL_GetError() );
        return image;
    }
    else {
        return image;
    }
}
