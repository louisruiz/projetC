#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "fonction.h"

// Image de taille maximale que nous traiterons
#define HAUTEURMAX 1025
#define LARGEURMAX 1025

// permet d'écrire plusieurs pixels par ligne dans le sortie du fichier
#define MAX_PIXELS_PER_LINE 25

// defnition du min tester sur sa marche sans en important juste math.h
#define MIN( x, y ) ( ( x ) < ( y ) ? ( x ) : ( y ) )

//def du tab 1 et 2 qui vont nous servir a stocker les matrice des images, avec des pixel de la forme p(i,j)
int TableauImage[HAUTEURMAX][LARGEURMAX];
int TableauImage2[HAUTEURMAX][LARGEURMAX];

int main(void)
{
    int hauteur  = 0;
    int largeur = 0;
    int maxPixel = 0;

    char* fichierEntrer = "index.pgm";
    char* fichierSortie = "_out1.pgm";

    Lit_Creer_TAB (TableauImage, &hauteur, &largeur, &maxPixel, fichierEntrer );

    /*for(int i = 0; i < HAUTEURMAX; i++)
    {
        for(int j = 0; j < LARGEURMAX; j++)
        {
            TableauImage2[i][j] = TableauImage[i][j];
        }
    }*/
    Traitement(TableauImage,TableauImage2,hauteur,largeur);

    // creer un nouveau fichier et ecrit ce que TableauImage contient
    Ecrit_nouveau_fichier ( fichierSortie, TableauImage, "# Création de l'image de sortie ", hauteur, largeur,maxPixel );

    printf ( "L'image %s avec le traitement donne %s, hauteur=%u, largeur=%u, maxPixel=%d\n", fichierEntrer,fichierSortie,hauteur,largeur,maxPixel ) ;

    //system("pause");
    return 0 ;
}
