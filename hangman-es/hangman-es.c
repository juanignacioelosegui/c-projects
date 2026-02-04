#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

#define DICCIONARIO "diccionario.txt"
#define VIDAS 6
#define MAX_PAL 32

/*
 *  Pregunté en Stack Overflow cómo hacer para quitar los tildes de
 *  las más de 100.000 palabras cargadas en el diccionario.
 *  
 *  Usé la librería iconv - https://www.gnu.org/software/libiconv/
 *  en la terminal, para sobreescribir la codificación UTF-8 a
 *  US-ASCII. No hay más tildes en el diccionario.
 *  Gracias a @pmt por ayudarme acá.
 */

//  Función para debugging. Printea todas las líneas.
//  No tengo itea de cómo funciona
static void cat( FILE * p )
{
    char buf[8];
    size_t nbytes;
    while ((nbytes = fread(buf, sizeof(char), sizeof(buf), p)) != 0)
    {
        fwrite(buf, sizeof(char), nbytes, stdout);
    }
}

static void limpiar_newline( char * s )
{
    s[strcspn(s, "\r\n")] = '\0';
}

static bool es_letra_ascii( const char c )
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

static bool validarIntento( char intento, const bool usadas[26] )
{
    if ( !es_letra_ascii(intento) )
    {
        printf("Meté una letra (a-z).\n");
        return false;
    }

    intento = (char)tolower((unsigned char)intento);
    int idx = intento - 'a';

    if ( idx < 0 || idx >= 26 )
    {
        printf("Solo letras a-z.\n");
        return false;
    }

    if ( usadas[idx] )
    {
        printf("Esa letra ya la probaste.\n");
        return false;
    }

    return true;
}

static void printEspacios( const char * estado )
{
    for (int i = 0; estado[i] != '\0'; i++) { printf("%c ", estado[i]); }

    printf("\n");
}

static bool updatePalabra( const char * palabra, char * estado, char intento )
{
    bool acierto = false;

    for ( int i = 0; palabra[i] != '\0'; i++ )
    {
        if ( tolower((unsigned char)palabra[i]) == intento )
        {
            estado[i] = palabra[i];
            acierto = true;
        }
    }

    return acierto;
}

static bool gano( const char * estado )
{
    return strchr(estado, '_') == NULL;
}

int main(void)
{
    printf("*** AHORCADO ***\n");
    short rounds = 3;

    // Semilla una sola vez (no por ronda)
    srand((unsigned)time(NULL));

    while (rounds > 0)
    {
        // Abrir diccionario
        FILE *ptr = fopen(DICCIONARIO, "r");

        if (!ptr)
        {
            perror("[DBG] No se pudo abrir diccionario.txt");
            return 1;
        }
        else
            printf("[DBG] Diccionario abierto.\n");

        //  printf("[DBG] Imprimiendo diccionario...\n");
        //  cat(ptr);
        //  printf("\n[DBG] Diccionario completo impreso.\n");

        //  Elegir palabra aleatoria
        //  Source - https://stackoverflow.com/a/20774074
        //  Posted by Farouq Jouti
        //  Retrieved 2026-01-30, License - CC BY-SA 3.0
        char palabra[MAX_PAL];
        int i = 0, ran = 0;

        for ( ; fgets(palabra, sizeof(palabra), ptr); i++ ) { ; }

        if ( i == 0 )
        {
            printf("[DBG] El diccionario está vacío.\n");
            fclose(ptr);
            return 1;
        }

        ran = rand(  ) % i;
        rewind( ptr );

        for ( i = 0; i < ran; i++ )
        {
            if ( !fgets(palabra, sizeof(palabra), ptr) )
            {
                printf("[DBG] Error leyendo el diccionario.\n");
                fclose( ptr );
                return 1;
            }
        }

        // Leer la palabra 
        if ( !fgets(palabra, sizeof(palabra), ptr) )
        {
            printf("[DBG] Error leyendo la palabra elegida.\n");
            fclose( ptr );
            return 1;
        }

        limpiar_newline( palabra );
        fclose( ptr );

        // Estado inicial
        size_t n = strlen( palabra );
        if ( n == 0 )
        {
            printf("[DBG] Palabra vacía (línea rara en diccionario). Salteo.\n");
            rounds--;
            continue;
        }

        if ( n >= MAX_PAL )
        {
            printf("Palabra demasiado larga para el buffer. Salteo.\n");
            rounds--;
            continue;
        }

        char estado[MAX_PAL];
        for ( size_t k = 0; k < n; k++ ) { estado[k] = '_'; }
        estado[n] = '\0';

        bool usadas[26] = {0};
        int vidas = VIDAS;

        while ( vidas > 0 && !gano(estado) )
        {
            printf("\nVidas: %d\n", vidas);
            printEspacios(estado);

            printf("Escribí una letra: ");
            char intento;

            if ( scanf(" %c", &intento) != 1 )
            {
                printf("No pude leer el input.\n");
                return 1;
            }

            while ( !validarIntento(intento, usadas) )
            {
                printf("Escribí una letra: ");
                if ( scanf(" %c", &intento) != 1 ) { return 1; }
            }

            intento = (char)tolower((unsigned char)intento);
            usadas[intento - 'a'] = true;

            bool acerto = updatePalabra(palabra, estado, intento);
            if ( !acerto )
            {
                printf("No está!\n");
                vidas--;
            } else { printf("Bien!\n"); }
        }

        if ( gano(estado) ) { printf("\nGanaste! La palabra era: %s\n", palabra); }
        else { printf("\nPerdiste! La palabra era: %s\n", palabra); }

        rounds--;
    }

    printf("\nFin del juego.\n");
    return 0;
}

