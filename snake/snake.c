#include <SDL2/SDL_events.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

//  Global variables
#define HEIGHT 600
#define WIDTH 900
#define GRID_SIZE 20

int main (int argc, const char * argv[])
{
    //  Initialize window
    SDL_Window * window = SDL_CreateWindow(
            "Snake by @juanielosegui",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WIDTH, HEIGHT,
            0);

    //  Initialize renderer
    SDL_Renderer * renderer = SDL_CreateRenderer(
        /* window   = */   window, 
        /* index    = */   -1,
        /* flags    = */   0
    );
                    
    
    //  Main game loop
    bool quit = false;
    SDL_Event event;
    while (!quit)
    {
        //  Handle events on queue
        while( SDL_PollEvent( &event ) != 0 )
        {
            //  User requests quit
            if( event.type == SDL_QUIT ) quit = true;

            //  Create grid
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);

            for (int x = 0; x <= WIDTH; x += GRID_SIZE)
            {
                SDL_RenderDrawLine(renderer, x, 0, x, HEIGHT);
            }

            for (int y = 0; y <= HEIGHT; y += GRID_SIZE)
            {
                SDL_RenderDrawLine(renderer, 0, y, WIDTH, y);
            }
            
            SDL_RenderPresent(renderer);
        }
    }

    return 0;
}
