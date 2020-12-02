#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/*QUESTION A DEMANDER AU PROF :

IMAGE A TRAITER UNIQUEMENT SOUS PGM format ASCII ?

pour la fonction min vaut il mieux limporter avec math.h ou la creer?


/* Filtre de sobel_1 1 :{

{-1,-2,-1},
{0, 0, 0},
{1, 2, 1}
}
Filtre de Sobel 2 {             LEQUEL UTILISER?

{-1,0,1},
{-2,0,2},
{-1,0,1}
}

QUESTION SUR LA MATRICE N*N : faut il rentrer nous meme une matrice de taille n*n pendant lexec?

est ce que je peut faire d'autre fonction qui ne sont pas demander ?


obliger d'avoir openCV pour ajouter des elements graphique?




*/

#define HAUTEURMAX 1025
#define LARGEURMAX 1025

// permet d'écrire plusieurs pixels par ligne dans le sortie du fichier
#define PIXELMAX 25

// defnition du min tester si sa marche sans, en important juste math.h
#define MIN( x, y ) ( ( x ) < ( y ) ? ( x ) : ( y ) )


//Definition du tableau de l'image

int TableauImage[HAUTEURMAX][LARGEURMAX];
int TableauImage2[HAUTEURMAX][LARGEURMAX];

FILE* Lire_entete(int* hauteur,int* largeur,int* maxPixel,char* pgmnom){

  static FILE* fp = 0L ;
  char pgmFormat[3] =  { '\0' } ;
  char ignore[80] = { '\0' } ;
  memset ( ( void * ) ignore, '\0', 80 ) ;
  fp = fopen ( pgmnom, "r" );
  if ( fp )
  {
    // Check the signature
    fscanf ( fp, "%2c\n", pgmFormat ) ;
    //printf ( "%s\n", pgmFormatFlag ) ;
    if ( ! strcmp ( pgmFormat, "P2" ) )
    {
      // Skip the comment line
      //fscanf ( fp, "\n" ) ;
      fgets (  ignore, 70, fp ) ;
      //printf ( "%s", trash ) ;
      // Read the widt
      fscanf ( fp, "%i", largeur ) ;
      //printf ( "%i,", *width ) ;
      // Read the height
      fscanf ( fp, "%i", hauteur ) ;
      //printf ( "%i\n", *height ) ;
      // Read the maximum pixel value
      fscanf ( fp, "%i", maxPixel );
    }
    //fclose ( fp ) ;
  }
  return fp;
}

void Lit_Creer_TAB(int Tab[][1025],int* hauteur,int* largeur,int* maxPixel,char* fichierEntrer){
    int ligne= 0 ;
    int col = 0 ;
    FILE* fp = Lire_entete ( hauteur,largeur, maxPixel,fichierEntrer) ;
    char ignore = ' ';
    char yesThreshold = ' ';

    if ( fp )
    {
        printf ( "infos de l'image d'entrer :  height=%d, width=%d\n", *hauteur, *largeur) ;
        for ( ligne= 0 ; ligne< MIN( HAUTEURMAX - 1, *hauteur ) ;ligne++ )
        {
            for ( col = 0 ; col < MIN( LARGEURMAX-1, *largeur ) ; col ++ )
            {
                fscanf ( fp, "%i", &Tab[ligne][col]) ;
            }
        }
        fclose ( fp ) ;
    }

    return ;
}


void Ecrit_nouveau_fichier(char* fichierSortie,int Tab[][1025],char* commentaire,int hauteur,int largeur,int maxPixel){
    int ligne = 0 ;
    int col = 0 ;
    FILE* fp = fopen ( fichierSortie, "w" ) ;
    if ( fp )
    {
        // Generate the header info
        fprintf ( fp, "P2\n" ) ;
        fprintf ( fp, "%s\n", commentaire) ;
        fprintf ( fp, "%u %u\n",largeur,hauteur ) ;
        fprintf ( fp, "%u\n", maxPixel ) ;

        // Now write out the data, ensuring that at most 70
        // values appear on each line, even if width is > 70
        for ( ligne= 0 ;ligne<hauteur; ligne++ )
        {
            for ( col = 0 ; col < largeur ; col ++ )
            {
                fprintf ( fp, "%u", Tab[ligne][col] ) ;
                // break up long rows into multiple lines as needed
                if ( PIXELMAX> 1 )
                {
                    fprintf ( fp, " " ) ;
                }
                if ( ( col % PIXELMAX ) == 0 )
                {
                    fprintf ( fp, "\n" ) ;
                }
            }
            // Watch out of special case of width == 70
            if ( col % PIXELMAX )
            {
                fprintf ( fp, "\n" ) ;
            }
        }
        fclose ( fp ) ;
    }
    return ;

}

//parcours la chaine et convertis les MAJ en minuscule pour faciliter les entrer (vu que la fct strcmp ne tient pas compte de la casse)
void lettreMIN(char chaine[30]){
  for(int i = 0; i < strlen(chaine); i++){
    chaine[i] = tolower(chaine[i]);
  }
}
// effectue le calcul entre un pixel(i,j) et une matrice de convolution donner en entrer
void conMatrixMult(int TableauImage[1025][1025], int TableauImage2[1025][1025], int Matrice[3][3], int i, int j, int diviseur, int soustraction)
{
  TableauImage[i][j] = (TableauImage[i+1][j+1]*Matrice[0][0] + TableauImage[i][j+1]*Matrice[0][1]+ TableauImage[i-1][j+1]*Matrice[0][2]+TableauImage[i+1][j]*Matrice[1][0]+TableauImage[i][j]*Matrice[1][1]+TableauImage[i-1][j]*Matrice[1][2]+TableauImage[i+1][j-1]*Matrice[2][0]+TableauImage[i][j+1]*Matrice[2][1]+TableauImage[i-1][j-1]*Matrice[2][2])/diviseur - soustraction;
}

void convolutionTEST(int TableauImage[1025][1025], int TableauImage2[1025][1025], int largeur, int hauteur){
   int boxBlur[3][3] = {
       { 1, 1, 1 },
       { 1,  1, 1 },
       { 1, 1, 1 }
   };

   int gaussian[3][3] = {
       {1, 2, 1},
       {2, 4, 2},
       {1, 2, 1}
   };
    int edgeDetect[3][3] = {
       {-1, -1, -1},
       {-1,  5, -1},
       {-1, -1, -1}
   };

   int sharpen[3][3] = {
       {0, -1,  0},
       {-1, 5, -1},
       {0, -1,  0}
   };


   char convolution[30];
   printf("Saisir le filtre à appliquer\n(Box, Gaussian, Edge) \n");
   scanf("%s", convolution);
   lettreMIN(convolution);

   if(strcmp(convolution, "box") == 0){
       for (int i = 1; i < HAUTEURMAX; i++) {
           for (int j = 1; j < LARGEURMAX; j++) {
               conMatrixMult(TableauImage, TableauImage2, boxBlur, i, j, 9, 0);

           }
       }
   }
   if(strcmp(convolution, "gaussian") == 0){
       for (int i = 1; i < HAUTEURMAX; i++) {
           for (int j = 1; j < LARGEURMAX; j++) {
               conMatrixMult(TableauImage,TableauImage2, gaussian, i, j, 16, 0);

           }
       }
   }
   if(strcmp(convolution, "edge") == 0){
       for (int i = 1; i < HAUTEURMAX; i++) {
           for (int j = 1; j < LARGEURMAX; j++) {
               conMatrixMult(TableauImage,TableauImage2, edgeDetect, i, j, 128, 0);

           }
       }
   }
   printf("L'image est délavée, désolé. Impossible de trouver un moyen de contourner cela. Elle est cependant affinée.");
}

void inversion(int TableauImage[1025][1025]){
   for (int i = 1; i < HAUTEURMAX; i++) {
       for (int j = 1; j < LARGEURMAX; j++) {
             TableauImage[i][j] = 255 - TableauImage[i][j];
       }
   }

}

void Seuil(int TableauImage[1025][1025]) {


   int seuil;
   printf("Entrez le seuil à appliquer (Entier compris entre 2 et 6 inclus)\n");
   scanf("%d", &seuil);

   for (int i = 0; i < HAUTEURMAX; i++){
       for (int j = 0; j < LARGEURMAX; j++){
           switch (seuil){

           case 1:
               printf("Le nombre doit etre entre 2 et 6\n");
               break;

           case 2:
               if (TableauImage[i][j] > (seuil-1)*255/seuil) {
                   TableauImage[i][j] = 255;
               }
               else {
                   TableauImage[i][j] = 0;
               }
               break;
           case 3:
               if (TableauImage[i][j] > (seuil-1)*255/seuil) {
                   TableauImage[i][j] = 255;
               }
               else if (TableauImage[i][j] > (seuil-2)*(255/seuil)){
                   TableauImage[i][j] = (seuil-2)*(255/seuil);
               }
               else {
                   TableauImage[i][j] = 0;
               }
               break;
           case 4:
               if (TableauImage[i][j] > (seuil-1)*255/seuil) {
                   TableauImage[i][j] = 255;
               }
               else if (TableauImage[i][j] > (seuil-2)*(255/seuil)){
                   TableauImage[i][j] = (seuil-2)*(255/seuil);
               }
               else if (TableauImage[i][j] > (seuil-3)*(255/seuil)){
                   TableauImage[i][j] = (seuil-3)*(255/seuil);
               }
               else {
                   TableauImage[i][j] = 0;
               }
               break;
           case 5:
               if (TableauImage[i][j] > (seuil-1)*255/seuil) {
                   TableauImage[i][j] = 255;
               }
               else if (TableauImage[i][j] > (seuil-2)*(255/seuil)){
                   TableauImage[i][j] = (seuil-2)*(255/seuil);
               }
               else if (TableauImage[i][j] > (seuil-3)*(255/seuil)){
                   TableauImage[i][j] = (seuil-3)*(255/seuil);
               }
               else if (TableauImage[i][j] > (seuil-4)*(255/seuil)){
                   TableauImage[i][j] = (seuil-4)*(255/seuil);
               }
               else {
                   TableauImage[i][j] = 0;
               }
               break;
           case 6:
               if (TableauImage[i][j] > (seuil-1)*255/seuil) {
                   TableauImage[i][j] = 255;
               }
               else if (TableauImage[i][j] > (seuil-2)*(255/seuil)){
                   TableauImage[i][j] = (seuil-2)*(255/seuil);
               }
               else if (TableauImage[i][j] > (seuil-3)*(255/seuil)){
                   TableauImage[i][j] = (seuil-3)*(255/seuil);
               }
               else if (TableauImage[i][j] > (seuil-4)*(255/seuil)){
                   TableauImage[i][j] = (seuil-4)*(255/seuil);
               }
               else if (TableauImage[i][j] > (seuil-5)*(255/seuil)){
                   TableauImage[i][j] = (seuil-5)*(255/seuil);
               }
               else {
                   TableauImage[i][j] = 0;
               }
               break;
           default:
               printf("Le nombre doit etre entre 2 et 6\n");
               break;
           }
       }
   }
}

void luminosite(int TableauImage[1025][1025]){
   char lum[10];
   double perc;
   printf("Voulez vous eclaircir ou assombrir l'image ? (Eclaircir, Assombrir) \n");
   scanf("%s", lum);
   lettreMIN(lum);

   printf("Entrer un pourcentage entre 0 et 100 \n");
   scanf("%lf", &perc);
   perc = 0.01* perc;


   if(strcmp(lum, "eclaircir") == 0){
       perc = 1.0 + perc;

       for (int i = 0; i < HAUTEURMAX; i++) {
           for (int j = 0; j < LARGEURMAX; j++) {
               if(perc*TableauImage[i][j]<= 255){
                   TableauImage[i][j] = perc*TableauImage[i][j];
               }
               else{
                   TableauImage[i][j] = 255;
               }
           }
       }
   }

   if(strcmp(lum, "assombrir") == 0){
       perc = 1.0 - perc;

       for (int i = 0; i < HAUTEURMAX; i++) {
           for (int j = 0; j < LARGEURMAX; j++) {
               TableauImage[i][j] = perc*TableauImage[i][j];

           }
       }
   }
}

void frame(int TableauImage[1025][1025], int largeur, int hauteur){
   int startPosX;
   int endPosX;
   int startPosY;
   int endPosY;
   int lum;

   printf("Enter leftmost X position (0-%d): ", largeur);
   scanf("%d", &startPosX);
   printf("\nEnter rightmost X position (0-%d): ", largeur);
   scanf("%d", &endPosX);
   printf("\nEnter topmost Y position (0-%d): ", hauteur);
   scanf("%d", &startPosY);
   printf("\nEnter bottommost Y position (0-%d): ", hauteur);
   scanf("%d", &endPosY);
   printf("\n");
   printf("Enter frame luminosity (0-255): ");
   scanf("%d", &lum);
   printf("\n");

   for(int i = 0; i < LARGEURMAX; i++){
       for(int j = 0; j < startPosY; j++){
           TableauImage[i][j] = lum;
       }
   }
   for(int i = 0; i < startPosX; i++){
       for(int j = startPosY; j < LARGEURMAX; j++){
           TableauImage[i][j] = lum;
       }
   }
   for(int i = startPosX; i < endPosX; i++){
       for(int j = endPosY; j < HAUTEURMAX; j++){
           TableauImage[i][j] = lum;
       }
   }
   for(int i = endPosX; i < LARGEURMAX; i++){
       for(int j = startPosY; j < HAUTEURMAX; j++){
           TableauImage[i][j] = lum;
       }
   }

}

void transformation(int TableauImage[1025][1025], int TableauImage2[1025][1025], int largeur, int hauteur){
   char tfm[10];
   int rotation;
   printf("Do you want to rotate the image or reflect the image? (Rotate, Reflect) \n");
   scanf("%s", tfm);
   lettreMIN(tfm);

   if (strcmp(tfm, "reflect") == 0) {
       printf("Do you want the image to be reflected vertically or horizontally?\n(Vertical, Horizontal)\n");
       char direction[15];
       scanf("%s", direction);
       lettreMIN(direction);


       if(strcmp(direction, "vertical") == 0){
           for(int i = 0; i < largeur; i++){
               for(int j = 0; j < hauteur; j++){
                   TableauImage2[i][j] = TableauImage[largeur-i][j];
               }
           }

           for(int i = 0; i < largeur; i++){
               for(int j = 0; j < hauteur; j++){
                   TableauImage[i][j] = TableauImage2[i][j];
               }
           }
       }

       if(strcmp(direction,"horizontal") == 0){
           for(int i = 0; i < largeur; i++){
               for(int j = 0; j < hauteur; j++){
                   TableauImage2[i][j] = TableauImage[i][hauteur-j];
               }
           }

           for(int i = 0; i < largeur; i++){
               for(int j = 0; j < hauteur; j++){
                   TableauImage[i][j] = TableauImage2[i][j];
               }
           }
       }
   }

   if(strcmp(tfm, "rotate") == 0) {
       printf("Do you want the image rotated 90, 180, or 270 degrees clockwise? ");
       scanf("%d", &rotation);

       if (rotation == 90){
           for(int i = 0; i < LARGEURMAX; i++){
               for(int j = 0; j < HAUTEURMAX; j++){
                   TableauImage2[i][j] = TableauImage[j][i];
               }
           }

           for(int i = 0; i < LARGEURMAX; i++){
               for(int j = 0; j < HAUTEURMAX; j++){
                   TableauImage[i][j] = TableauImage2[i][j];
               }
           }
       }

        if(rotation ==  180) {
            for(int i = 0; i < largeur; i++){
               for(int j = 0; j < largeur; j++){
                   TableauImage2[i][j] = TableauImage[largeur-i][hauteur-j];
               }
           }

           for(int i = 0; i < largeur; i++){
               for(int j = 0; j < hauteur; j++){
                   TableauImage[i][j] = TableauImage2[i][j];
               }
           }
       }

       if (rotation == 270){
           for(int i = 0; i < largeur; i++){
               for(int j = 0; j < hauteur; j++){
                   TableauImage2[i][j] = TableauImage[hauteur-j][i];
               }
           }

           for(int i = 0; i < largeur; i++){
               for(int j = 0; j < hauteur; j++){
                   TableauImage[i][j] = TableauImage2[i][j];
               }
           }
       }
   }
}

void Traitement(int TableauImage[1025][1025], int TableauImage2[1025][1025], int hauteur, int largeur) {
    char inputFunc[30];

    printf("Entrer le traitement à appliquer sur l'image. (Seuil, Luminosite,\nFraming, Transformation, Convolution, Inversion) \n");
    scanf("%s", inputFunc);
    lettreMIN(inputFunc);

    if(strcmp(inputFunc,"inversion") == 0) {
        inversion(TableauImage);
    }

    if(strcmp(inputFunc,"convolution") == 0) {
        convolutionTEST(TableauImage,TableauImage2,hauteur,largeur);
    }

    if(strcmp(inputFunc, "seuil") == 0){
        Seuil(TableauImage);
    }

    if(strcmp(inputFunc, "luminosite") == 0){
        luminosite(TableauImage);
    }

    if(strcmp(inputFunc, "framing") == 0){
        frame(TableauImage,hauteur,largeur);
    }

    if(strcmp(inputFunc,"transformation") == 0) {
        transformation(TableauImage,TableauImage2,hauteur,largeur);
    }

    printf("\nFin\n");
}
