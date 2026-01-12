#include <SDL2/SDL_events.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

//  Global variables
#define HEIGHT 600
#define WIDTH 900
#define GRID_SIZE 20
#define COLS ( WIDTH / GRID_SIZE )    //  45
#define ROWS ( HEIGHT / GRID_SIZE )   //  30

typedef struct {
    int x;
    int y;
} Cell;

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Dir;

static void draw_grid( SDL_Renderer * r )
{
    SDL_SetRenderDrawColor(r, 50, 50, 50, 255);

    for (int x = 0; x <= WIDTH; x += GRID_SIZE)
    {
        SDL_RenderDrawLine(r, x, 0, x, HEIGHT);
    }

    for (int y = 0; y <= HEIGHT; y += GRID_SIZE)
    {
        SDL_RenderDrawLine(r, 0, y, WIDTH, y);
    }
}

static void draw_cell( SDL_Renderer * r, Cell c, Uint8 R, Uint8 G, Uint8 B )
{
    SDL_Rect rect = { 
        /* x = */   c.x * GRID_SIZE, 
        /* y = */   c.y * GRID_SIZE, 
        /* w = */   GRID_SIZE, 
        /* h = */   GRID_SIZE };
    SDL_SetRenderDrawColor(r, R, G, B, 255);
    SDL_RenderFillRect(r, &rect);
}

static bool cell_equals(Cell a, Cell b)
{ 
    return (a.x == b.x && a.y == b.y); 
}

static bool cell_in_snake(Cell c, const Cell * snake, int len)
{
    for ( int i = 0; i < len; i++ )
    {
        if ( cell_equals(c, snake[i]) ) return true;
    }
    return false;
}

static Cell random_free_cell( const Cell *snake, int len ) {
    Cell c;
    do {
        c.x = rand() % COLS;
        c.y = rand() % ROWS;
    } while ( cell_in_snake(c, snake, len) );
    return c;
}

int main ( int argc, const char * argv[] )
{
    //  Generate random seed
    srand( (unsigned)time(NULL) );

    //  Initialize window
    SDL_Window * window = SDL_CreateWindow(
            "Snake by @juanignacioelosegui",
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
                 
    //  Create snake
    Cell snake[COLS * ROWS];
    int snake_len = 3;
    snake[0] = (Cell){ COLS/2, ROWS/2 };
    snake[1] = (Cell){ COLS/2 - 1, ROWS/2 };
    snake[2] = (Cell){ COLS/2 - 2, ROWS/2 };
    Dir dir = RIGHT;
    
    // Create apple
    Cell apple = random_free_cell( snake, snake_len );

    //  Set velocity
    const Uint32 TICK_MS = 120;
    Uint32 last_tick = SDL_GetTicks();

    //  Main game loop
    bool quit = false;
    SDL_Event event;
    
    while ( !quit )
    {
        // input
        while ( SDL_PollEvent(&event) )
        {
            //  Close window button
            if ( event.type == SDL_QUIT ) quit = true;

            //  Keystrokes
            if ( event.type == SDL_KEYDOWN )
            {
                switch ( event.key.keysym.sym )
                {
                    case SDLK_UP:    if ( dir != DOWN )  dir = UP; break;
                    case SDLK_DOWN:  if ( dir != UP )    dir = DOWN; break;
                    case SDLK_LEFT:  if ( dir != RIGHT ) dir = LEFT; break;
                    case SDLK_RIGHT: if ( dir != LEFT )  dir = RIGHT; break;
                }
            }
        }

        //  Update tickrate
        Uint32 now = SDL_GetTicks();
        if ( now - last_tick >= TICK_MS )
        {
            last_tick = now;

            //  New head on grid
            Cell head = snake[0];
            Cell new_head = head;
            if ( dir == UP ) new_head.y--;
            if ( dir == DOWN ) new_head.y++;
            if ( dir == LEFT ) new_head.x--;
            if ( dir == RIGHT ) new_head.x++;

            //  Limits and "game over" ending
            if ( new_head.x < 0 || new_head.x >= COLS || new_head.y < 0 || new_head.y >= ROWS ) quit = true;
            //  Snake crashes with itself
            if ( cell_in_snake(new_head, snake, snake_len) ) quit = true;
            
            //  Insert head
            for ( int i = snake_len; i > 0; i-- ) snake[i] = snake[i - 1];
            snake[0] = new_head;

            //  Eat apple?
            if ( cell_equals(new_head, apple) )
            {
                //  Snake will only increase its size
                //      only when it eats the apple
                snake_len++;
                apple = random_free_cell( snake, snake_len ); 
            }
        }

        // render
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
        SDL_RenderClear( renderer );

        draw_grid( renderer );
        //  Apple color
        draw_cell( renderer, apple, 220, 40, 40 );
        //  Snake color
        for ( int i = 0; i < snake_len; i++ )
        {
            draw_cell( renderer, snake[i], 40, 200, 40 ); // snake verde
        }

        SDL_RenderPresent( renderer );
    }

    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    SDL_Quit();
    return 0;
}
