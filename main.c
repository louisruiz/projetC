#define MAX_LONGUEUR 1025
#define MAX_LARGEUR 1025
#define MAX_PIXELS_PER_LINE 25

#define MIN( x, y ) ( ( x ) < ( y ) ? ( x ) : ( y ) )

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#include "fonction.h"

int theImageArray[1025][MAX_LARGEUR];
int theImageArrayDup[1025][MAX_LARGEUR];

FILE* read_pgm_file_info
(
    int* height,    // output
    int* width,    // output
    int* maxPixel,  // outputpgmOutFileName,
    char* pgmFname // input
)
{
    static FILE* fp = 0L ;
    char pgmFormatFlag[3] =  { '\0' } ;

    char trash[80] = { '\0' } ;
    memset ( ( void * ) trash, '\0', 80 ) ;

    fp = fopen ( pgmFname, "r" ) ;

    if ( fp )
    {
        // Check the signature
        fscanf ( fp, "%2c\n", pgmFormatFlag ) ;
        //printf ( "%s\n", pgmFormatFlag ) ;
        if ( ! strcmp ( pgmFormatFlag, "P2" ) )
        {
            // Skip the comment line
            //fscanf ( fp, "\n" ) ;
            fgets (  trash, 70, fp ) ;
            //printf ( "%s", trash ) ;
            pgmFname,
            // Read the width
            fscanf ( fp, "%i", width ) ;
            //printf ( "%i,", *width ) ;

            // Read the height
            fscanf ( fp, "%i", height ) ;
            //printf ( "%i\n", *height ) ;

            // Read the maximum pixel value
            fscanf ( fp, "%i", maxPixel ) ;
        }
        //fclose ( fp ) ;
    }


    return fp ;
}


void Lire_fichier_dansTableau
(
    int imageArray[][MAX_LONGUEUR],
    int* height,
    int* width,
    int* maxP,
    char* fichierENTRER
)
{
    int row = 0 ;
    int col = 0 ;
    FILE* fp = read_pgm_file_info ( height, width, maxP, fichierENTRER ) ;
    char trash = ' ';
    char yesThreshold = ' ';

    if ( fp )
    {
        printf ( "reading height=%d, width=%d\n", *height, *width ) ;
        for ( row = 0 ; row < MIN( MAX_LONGUEUR - 1, *height ) ; row ++ )
        {
            for ( col = 0 ; col < MIN( MAX_LARGEUR -1, *width ) ; col ++ )
            {
                fscanf ( fp, "%i", &imageArray[row][col]) ;
            }
        }
        fclose ( fp ) ;
    }

    return ;
}

void Ecire_fichier_dansTableau
(
    char* fichierSORTIE,
    int imageArray[][MAX_LARGEUR],
    char* commentLine,
    int height,
    int width,
    int maxP
)
{
    int row = 0 ;
    int col = 0 ;
    FILE* fp = fopen ( fichierSORTIE, "w" ) ;
    if ( fp )
    {
        // Generate the header info
        fprintf ( fp, "P2\n" ) ;
        fprintf ( fp, "%s\n", commentLine ) ;
        fprintf ( fp, "%u %u\n", width, height ) ;
        fprintf ( fp, "%u\n", maxP ) ;

        // Now write out the data, ensuring that at most 70
        // values appear on each line, even if width is > 70
        for ( row = 0 ; row < height ; row ++ )
        {
            for ( col = 0 ; col < width ; col ++ )
            {
                fprintf ( fp, "%u", imageArray[row][col] ) ;
                // break up long rows into multiple lines as needed
                if ( MAX_PIXELS_PER_LINE > 1 )
                {
                    fprintf ( fp, " " ) ;
                }
                if ( ( col % MAX_PIXELS_PER_LINE ) == 0 )
                {
                    fprintf ( fp, "\n" ) ;
                }
            }
            // Watch out of special case of width == 70
            if ( col % MAX_PIXELS_PER_LINE )
            {
                fprintf ( fp, "\n" ) ;
            }
        }
        fclose ( fp ) ;
    }
    return ;
}



int main()
{
    int height,width,maxP;
    char* fichierENTRER = "irv.pgm" ;
    char* fichierSORTIE = "irv_out.pgm" ;
    //Lire le fichier dans le tableau
    Lire_fichier_dansTableau(theImageArray,&height,&width,&maxP,fichierENTRER);
    //transformer l'image
    for(int i = 0; i < 1025; i++)
    {
      for(int j = 0; j < MAX_LARGEUR; j++)
      {
        theImageArrayDup[i][j] = theImageArray[i][j];
      }
    }
    TraitementImage(theImageArray,theImageArrayDup,height,width);
    Ecire_fichier_dansTableau(fichierSORTIE,theImageArray,"# JR test file",height,width,maxP);
    printf ( "Copie %s a %s, longueur=%u, largeur=%u, pixel maximum=%d\n", fichierENTRER,fichierSORTIE,height, width, maxP) ;

    return 0;
}
