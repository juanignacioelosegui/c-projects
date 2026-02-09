#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define WIDTH 900
#define HEIGHT 600

//  Registra si se clickeó dentro de los límites del botón
static bool point_in_rect( int x, int y, const SDL_Rect * r )
{
    return ( x >= r->x && x < r->x + r->w && y >= r->y && y < r->y + r->h );
}

int main( int argc, char *argv[] )
{
    //  Manejar argumentos (candidatos)
    if ( argc < 3 )
    {
        fprintf( stderr, "Uso: %s \"Candidato1\" \"Candidato2\"\n", argv[0] );
        return EXIT_FAILURE;
    }

    const char *cand1 = argv[1];
    const char *cand2 = argv[2];

    //  Iniciar driver de video
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        fprintf( stderr, "[DBG] SDL no pudo arrancar! Error: %s\n", SDL_GetError() );
        return EXIT_FAILURE;
    }

    //  Crear ventana
    SDL_Window * window = SDL_CreateWindow(
        "Sistema de Votación",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT,
        SDL_WINDOW_SHOWN);

    if ( !window )
    {
        fprintf( stderr, "[DBG] No se pudo crear la ventana! Error: %s\n", SDL_GetError() );
        SDL_Quit();
        return EXIT_FAILURE;
    }

    //  Crear renderer
    SDL_Renderer * renderer = SDL_CreateRenderer(
        window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if ( !renderer )
    {
        fprintf( stderr, "No se pudo crear renderer: %s\n", SDL_GetError() );
        SDL_DestroyWindow( window );
        SDL_Quit();
        return EXIT_FAILURE;
    }

    //  Crear botones
    SDL_Rect btn1 = { 100, 200, 300, 150 };
    SDL_Rect btn2 = { 500, 200, 300, 150 };

    //  Crear contadores de votos
    int votos1 = 0;
    int votos2 = 0;

    SDL_Event e;
    bool run = true;

    while ( run )
    {
        //  Eventos
        while ( SDL_PollEvent(&e) )
        {
            //  Cerrar ventana si el usuario quiere
            if (e.type == SDL_QUIT) run = false;

            //  Incrementar votos según qué botón se presione
            else if ( e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT )
            {
                int mx = e.button.x;
                int my = e.button.y;

                if ( point_in_rect(mx, my, &btn1) )
                {
                    votos1++;
                    printf( "Voto para %s | %d - %d\n", cand1, votos1, votos2 );
                } 
                else if ( point_in_rect(mx, my, &btn2) )
                {
                    votos2++;
                    printf( "Voto para %s | %d - %d\n", cand2, votos1, votos2 );
                }
            }
            //  Otros botones
            else if ( e.type == SDL_KEYDOWN )
            {
                //  La R se usa para resetear los votos
                if ( e.key.keysym.sym == SDLK_r )
                {
                    votos1 = 0;
                    votos2 = 0;
                    printf( "Reset | %d - %d\n", votos1, votos2 );
                }
                //  Con escape se sale del programa
                else if ( e.key.keysym.sym == SDLK_ESCAPE ) run = false;
            }
        }

        //  Dibujar
        SDL_SetRenderDrawColor( renderer, 30, 30, 30, 255 );
        SDL_RenderClear( renderer );

        SDL_SetRenderDrawColor( renderer, 60, 120, 220, 255 );
        SDL_RenderFillRect( renderer, &btn1 );

        SDL_SetRenderDrawColor( renderer, 220, 80, 80, 255 );
        SDL_RenderFillRect( renderer, &btn2 );

        SDL_SetRenderDrawColor( renderer, 240, 240, 240, 255 );
        SDL_RenderDrawRect( renderer, &btn1 );
        SDL_RenderDrawRect( renderer, &btn2 );

        SDL_RenderPresent( renderer );
    }

    //  Limpiar todo
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    SDL_Quit();
    return EXIT_SUCCESS;
}

