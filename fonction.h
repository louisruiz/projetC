#define MAX_HEIGHT 1025
   #define MAX_WIDTH 1025
   #include <stdio.h>
   #include <math.h>
   #include <string.h>
   #include <ctype.h>

void lowerletter(char myString[30]){
  for(int i = 0; i < strlen(myString); i++){
    myString[i] = tolower(myString[i]);
  }
}

void invert(int theImageArray[1025][1025])
{
  for (int i = 1; i < MAX_HEIGHT; i++)
  {
    for (int j = 1; j < MAX_WIDTH; j++)
    {
      theImageArray[i][j] = 255 - theImageArray[i][j];
    }
  }
}


void threshold(int theImageArray[1025][1025]) {


   int n;
   printf("Enter the number of levels you wish to threshold by. \n(Integer between 2-6 inclusive). \n");
   scanf("%d", &n);

   for (int i = 0; i < MAX_HEIGHT; i++) {
       for (int j = 0; j < MAX_WIDTH; j++) {
           switch (n){

           case 1:
               printf("Invalid response. Please start over. /n");
               break;

           case 2:
               if (theImageArray[i][j] > (n-1)*255/n) {
                   theImageArray[i][j] = 255;
               }
               else {
                   theImageArray[i][j] = 0;
               }
               break;
           case 3:
               if (theImageArray[i][j] > (n-1)*255/n) {
                   theImageArray[i][j] = 255;
               }
               else if (theImageArray[i][j] > (n-2)*(255/n)){
                   theImageArray[i][j] = (n-2)*(255/n);
               }
               else {
                   theImageArray[i][j] = 0;
               }
               break;
           case 4:
               if (theImageArray[i][j] > (n-1)*255/n) {
                   theImageArray[i][j] = 255;
               }
               else if (theImageArray[i][j] > (n-2)*(255/n)){
                   theImageArray[i][j] = (n-2)*(255/n);
               }
               else if (theImageArray[i][j] > (n-3)*(255/n)){
                   theImageArray[i][j] = (n-3)*(255/n);
               }
               else {
                   theImageArray[i][j] = 0;
               }
               break;
           case 5:
               if (theImageArray[i][j] > (n-1)*255/n) {
                   theImageArray[i][j] = 255;
               }
               else if (theImageArray[i][j] > (n-2)*(255/n)){
                   theImageArray[i][j] = (n-2)*(255/n);
               }
               else if (theImageArray[i][j] > (n-3)*(255/n)){
                   theImageArray[i][j] = (n-3)*(255/n);
               }
               else if (theImageArray[i][j] > (n-4)*(255/n)){
                   theImageArray[i][j] = (n-4)*(255/n);
               }
               else {
                   theImageArray[i][j] = 0;
               }
               break;
           case 6:
               if (theImageArray[i][j] > (n-1)*255/n) {
                   theImageArray[i][j] = 255;
               }
               else if (theImageArray[i][j] > (n-2)*(255/n)){
                   theImageArray[i][j] = (n-2)*(255/n);
               }
               else if (theImageArray[i][j] > (n-3)*(255/n)){
                   theImageArray[i][j] = (n-3)*(255/n);
               }
               else if (theImageArray[i][j] > (n-4)*(255/n)){
                   theImageArray[i][j] = (n-4)*(255/n);
               }
               else if (theImageArray[i][j] > (n-5)*(255/n)){
                   theImageArray[i][j] = (n-5)*(255/n);
               }
               else {
                   theImageArray[i][j] = 0;
               }
               break;
           default:
               printf("Invalid response. Please start over. /n");
               break;
           }
       }
   }
}

void luminosity(int theImageArray[1025][1025]) {
   char lum[10];
   double perc;
   printf("Do you want to lighten or darken the image? (Lighten, Darken) \n");
   scanf("%s", lum);
   lowerletter(lum);

   printf("Enter a percentage between 0 and 100 (without the %%) of how much you want\nthe luminosity to change by. \n");
   scanf("%lf", &perc);
   perc = 0.01* perc;


   if(strcmp(lum, "lighten") == 0){
       perc = 1.0 + perc;

       for (int i = 0; i < MAX_HEIGHT; i++) {
           for (int j = 0; j < MAX_WIDTH; j++) {
               if(perc*theImageArray[i][j]<= 255){
                   theImageArray[i][j] = perc*theImageArray[i][j];
               }
               else{
                   theImageArray[i][j] = 255;
               }
           }
       }
   }

   if(strcmp(lum, "darken") == 0){
       perc = 1.0 - perc;

       for (int i = 0; i < MAX_HEIGHT; i++) {
           for (int j = 0; j < MAX_WIDTH; j++) {
               theImageArray[i][j] = perc*theImageArray[i][j];

           }
       }
   }
}

void frame(int theImageArray[1025][1025], int width, int height){
   int startPosX;
   int endPosX;
   int startPosY;
   int endPosY;
   int lum;

   printf("Enter leftmost X position (0-%d): ", width);
   scanf("%d", &startPosX);
   printf("\nEnter rightmost X position (0-%d): ", width);
   scanf("%d", &endPosX);
   printf("\nEnter topmost Y position (0-%d): ", height);
   scanf("%d", &startPosY);
   printf("\nEnter bottommost Y position (0-%d): ", height);
   scanf("%d", &endPosY);
   printf("\n");
   printf("Enter frame luminosity (0-255): ");
   scanf("%d", &lum);
   printf("\n");

   for(int i = 0; i < MAX_WIDTH; i++){
       for(int j = 0; j < startPosY; j++){
           theImageArray[i][j] = lum;
       }
   }
   for(int i = 0; i < startPosX; i++){
       for(int j = startPosY; j < MAX_HEIGHT; j++){
           theImageArray[i][j] = lum;
       }
   }
   for(int i = startPosX; i < endPosX; i++){
       for(int j = endPosY; j < MAX_HEIGHT; j++){
           theImageArray[i][j] = lum;
       }
   }
   for(int i = endPosX; i < MAX_WIDTH; i++){
       for(int j = startPosY; j < MAX_HEIGHT; j++){
           theImageArray[i][j] = lum;
       }
   }

}

void transformation(int theImageArray[1025][1025], int theImageArrayDup[1025][1025], int width, int height){
   char tfm[10];
   int rotation;
   printf("Do you want to rotate the image or reflect the image? (Rotate, Reflect) \n");
   scanf("%s", tfm);
   lowerletter(tfm);

   if (strcmp(tfm, "reflect") == 0) {
       printf("Do you want the image to be reflected vertically or horizontally?\n(Vertical, Horizontal)\n");
       char direction[15];
       scanf("%s", direction);
       lowerletter(direction);


       if(strcmp(direction, "vertical") == 0){
           for(int i = 0; i < width; i++){
               for(int j = 0; j < height; j++){
                   theImageArrayDup[i][j] = theImageArray[width-i][j];
               }
           }

           for(int i = 0; i < width; i++){
               for(int j = 0; j < height; j++){
                   theImageArray[i][j] = theImageArrayDup[i][j];
               }
           }
       }

       if(strcmp(direction,"horizontal") == 0){
           for(int i = 0; i < width; i++){
               for(int j = 0; j < height; j++){
                   theImageArrayDup[i][j] = theImageArray[i][height-j];
               }
           }

           for(int i = 0; i < width; i++){
               for(int j = 0; j < height; j++){
                   theImageArray[i][j] = theImageArrayDup[i][j];
               }
           }
       }
   }

   if(strcmp(tfm, "rotate") == 0) {
       printf("Do you want the image rotated 90, 180, or 270 degrees clockwise? ");
       scanf("%d", &rotation);

       if (rotation == 90){
           for(int i = 0; i < MAX_WIDTH; i++){
               for(int j = 0; j < MAX_HEIGHT; j++){
                   theImageArrayDup[i][j] = theImageArray[j][i];
               }
           }

           for(int i = 0; i < MAX_WIDTH; i++){
               for(int j = 0; j < MAX_HEIGHT; j++){
                   theImageArray[i][j] = theImageArrayDup[i][j];
               }
           }
       }

        if(rotation ==  180) {
            for(int i = 0; i < width; i++){
               for(int j = 0; j < height; j++){
                   theImageArrayDup[i][j] = theImageArray[width-i][height-j];
               }
           }

           for(int i = 0; i < width; i++){
               for(int j = 0; j < height; j++){
                   theImageArray[i][j] = theImageArrayDup[i][j];
               }
           }
       }

       if (rotation == 270){
           for(int i = 0; i < width; i++){
               for(int j = 0; j < height; j++){
                   theImageArrayDup[i][j] = theImageArray[height-j][i];
               }
           }

           for(int i = 0; i < width; i++){
               for(int j = 0; j < height; j++){
                   theImageArray[i][j] = theImageArrayDup[i][j];
               }
           }
       }
   }
}

void imageProcessing(int theImageArray[1025][1025], int theImageArrayDup[1025][1025], int height, int width) {
    char inputFunc[30];

    printf("Enter the function you wish to apply to your image. (Threshold, Luminosity,\nFraming, Transform, Convolve, Invert) \n");
    scanf("%s", inputFunc);
    lowerletter(inputFunc);

    if(strcmp(inputFunc,"invert") == 0) {
        invert(theImageArray);
    }

    if(strcmp(inputFunc, "threshold") == 0){
        threshold(theImageArray);
    }

    if(strcmp(inputFunc, "luminosity") == 0){
        luminosity(theImageArray);
    }

    if(strcmp(inputFunc, "framing") == 0){
        frame(theImageArray, height, width);
    }

    if(strcmp(inputFunc,"transform") == 0) {
        transformation(theImageArray, theImageArrayDup, height, width);
    }


    printf("\nDone\n");
}
