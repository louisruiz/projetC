#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "fonction.h"

#define MAX_LONGUEUR 1025
#define MAX_LARGEUR 1025

// entrer une taille, elle creer la structure
Image* NouvelleImage(int w,int h)
{
	Image* I = malloc(sizeof(Image));
	I->w = w;
	I->h = h;
	I->dat = calloc(1,w*h*sizeof(Pixel*));
	return I;
}

//recopie une img
Image* CopieImage(Image* I)
{
	Image* res;
	if (!I)
		return NULL;
	res = NouvelleImage(I->w,I->h);
	memcpy(res->dat,I->dat,I->w*I->h*sizeof(Pixel));
	return res;
}

//supprime une img
void SupprimeImage(Image* I)
{
	if (I)
	{
		free(I->dat);
		free(I);
	}
}

//donnez l'image, les coordonnées i,j du pixel voulu (lis le pixel en mémoire)
void Lis_Pixel(Image* I,int i,int j,Pixel p)
{
	assert(I && i>=0 && i<I->w && j>=0 && j<I->h);
	I->dat[I->w*j+i] = p;
}
//donnez l'image, les coordonnées i,j du pixel voulu (ecrit le pixel en mémoire)
Pixel Ecrit_Pixel(Image* I,int i,int j)
{
	assert(I && i>=0 && i<I->w && j>=0 && j<I->h);
	return I->dat[I->w*j+i];
}
//Charge une image
Image* Charger(const char* fichier)
{
	int i,j,max;
	char buf[10];
	Image* I;
	FILE* F = fopen(fichier,"r");
	if (!F)
		return NULL;
	fscanf(F,"%s %d %d %d",buf,&i,&j,&max);
	I = NouvelleImage(i,j);
	for(i=0;i<I->w*I->h;i++)
	{
		int r,g,b;
		fscanf(F,"%d %d %d",&r,&g,&b);
		I->dat[i].r = (unsigned char)r;
		I->dat[i].g = (unsigned char)g;
		I->dat[i].b = (unsigned char)b;
	}
	fclose(F);
	return I;
}
//sauvegarde une image
int Sauver(Image* I,const char* fichier)
{
	int i;
	FILE* F = fopen(fichier,"w");
	if (!F)
		return -1;
	// P5 format pgm
	fprintf(F,"P5\n%d %d\n255\n",I->w,I->h);
	for(i=0;i<I->w*I->h;i++)
		fprintf(F,"%d %d %d ",I->dat[i].r,I->dat[i].g,I->dat[i].b);
	fclose(F);
	return 0;
}

void lowerletter(char myString[30]){
  for(int i = 0; i < strlen(myString); i++){
    myString[i] = tolower(myString[i]);
  }
}

void inversion(int theImageArray[1025][1025]){
   for (int i = 1; i < MAX_LONGUEUR; i++)
   {
       for (int j = 1; j < MAX_LARGEUR; j++)
       {
             theImageArray[i][j] = 255 - theImageArray[i][j];
       }
   }

}

void TraitementImage(int theImageArray[1025][1025], int theImageArrayDup[1025][1025], int height, int width) {
    char inputFunc[30];

    printf("Entre la fonction que tu veut aplliquer a ton image. (inversion) \n");
    scanf("%s", inputFunc);
    lowerletter(inputFunc);

    if(strcmp(inputFunc,"Inversion") == 0) {
        inversion(theImageArray);
    }

    printf("\nDone\n");
}
