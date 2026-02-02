#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DICCIONARIO "diccionario.txt"

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
    char   buf[8];
    size_t nbytes;
    while ( (nbytes = fread(buf, sizeof(char), sizeof(buf), p)) != 0 )
    {
        fwrite( buf, sizeof(char), nbytes, stdout );
    }
}

int main (  )
{
    printf("*** AHORCADO ***\n");
    short rounds = 5;

    while ( rounds > 0 )
    {
        //  Abrir diccionario
        FILE * ptr = fopen( DICCIONARIO, "r" );
        
        if ( !ptr )
        {
            perror("[DBG] No se pudo abrir diccionario.txt\n");
            return 1;
        } else printf("[DBG] Diccionario abierto.\n");
        
        //  printf("[DBG] Imprimiendo diccionario...\n");
        //  cat(ptr);
        //  printf("\n[DBG] Diccionario completo impreso.\n");

        //  Elegir palabra aleatoria
        //  Source - https://stackoverflow.com/a/20774074
        //  Posted by Farouq Jouti
        //  Retrieved 2026-01-30, License - CC BY-SA 3.0
        char palabra[32];
        int i = 0 , ran = 0;
        srand( time(NULL) );
        for( ; fgets(palabra , sizeof(palabra) , ptr) ; i++ ) { ; }
        ran = rand(  ) % i;
        rewind( ptr );
        for( i = 0 ; i < ran ; i++ )
        {
            fgets( palabra , sizeof(palabra) , ptr );
        }

        printf("[DBG] Palabra aleatoria: %s\n", palabra);
        printf("[DBG] Longitud de la palabra: %ld\n", strlen(palabra)-1);

        

        rounds--;

    }



    return 0;
}
