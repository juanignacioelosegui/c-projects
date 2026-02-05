#include <stdio.h>
#include <SDL2/SDL.h>

#define WIDTH 900
#define HEIGHT 600

int main ( int argc, const char * argv[] )
{
    int SDL_Init();
    
    SDL_Window * window = 
        SDL_CreateWindow(
                "Sistema de Votación",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                WIDTH, HEIGHT, 0);

    printf("Hello world!\n");
    return 0;
}
