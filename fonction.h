#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void transformation(int TableauImage[1025][1025], int TableauImage2[1025][1025], int largeur, int hauteur);
void frame(int TableauImage[1025][1025], int largeur, int hauteur);
void luminosite(int TableauImage[1025][1025]);
void convolutionTEST(int TableauImage[1025][1025], int TableauImage2[1025][1025], int largeur, int hauteur);
void conMatrixMult(int TableauImage[1025][1025], int TableauImage2[1025][1025], int Matrice[3][3], int i, int j, int diviseur, int soustraction);
void lettreINF(char chaine[30]);
void Inversion(int TableauImage[1025][1025]);
void Seuil(int TableauImage[1025][1025]);
void Traitement(int TableauImage[1025][1025], int TableauImage2[1025][1025], int hauteur, int largeur);
//lis les infos de lentete de l'image d'entrer et les stock
FILE* Lire_entete(int* hauteur,int* largeur,int* maxPixel,char* pgmnom);
//lis les infos dans lentete et creer un tableau a partir de celle ci
void Lit_Creer_TAB(int Tab[][1025],int* hauteur,int* largeur,int* maxPixel,char* fichierEntrer);
//ecriture du nouveau fichier a partir du nouveau tableau qui a ete changé grace a traitement
void Ecrit_nouveau_fichier(char* fichierSortie,int Tab[][1025],char* commentaire,int hauteur,int largeur,int maxPixel);
