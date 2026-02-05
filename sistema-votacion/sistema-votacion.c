#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define WIDTH 900
#define HEIGHT 600

int main ( int argc, const char * argv[] )
{
    if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 ) { printf( "[DBG] SDL couldn't initialise! Error: %s\n", SDL_GetError() ); }

    SDL_Window * window = SDL_CreateWindow( 
            "Sistema de Votación",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WIDTH, HEIGHT, 0);
    
    if ( window == NULL ) { printf( "[DBG] Window couldn't be created! Error: %s\n", SDL_GetError() ); }

    SDL_Event e;
    while ( true )
    {
        if ( SDL_PollEvent(&e) )
        {
            if ( SDL_QUIT == e.type ) break;
        }
    }

    SDL_DestroyWindow( window );
    SDL_Quit();

    return EXIT_SUCCESS;
}
