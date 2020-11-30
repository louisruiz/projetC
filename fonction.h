#ifndef _QUICKIMAGE_H
#define _QUICKIMAGE_H

//Un pixel, c'est 3 couleurs : rouge, vert, bleu, qui varient de 0 à 255 chacun.
typedef struct Pixel
{
	unsigned char r,g,b;
} Pixel;

typedef struct Image
{
	int w,h;
	Pixel* dat;
} Image;

Image* Charger(const char* fichier);
int Sauver(Image*,const char* fichier);
Image* NouvelleImage(int w,int h);
Image* CopieImage(Image*);
void Lis_Pixel(Image*,int i,int j,Pixel p);
Pixel Ecrit_Pixel(Image*,int i,int j);
void SupprimeImage(Image*);
void lowerletter(char myString[30]);
void inversion(int theImageArray[1025][1025]);
void TraitementImage(int theImageArray[1025][1025], int theImageArrayDup[1025][1025], int height, int width);

#endif
