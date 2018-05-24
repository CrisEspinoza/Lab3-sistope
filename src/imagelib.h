# include <stdlib.h>

# include "../utils/bmplib.h"
# include "../utils/bmplib.c"

# ifndef _IMAGELIB_H_
# define _IMAGELIB_H_

// Estas son las cabeceras de las funciones que se ocupan dentro del programa


Image* initImage(int height, int width);
Image* loadImage(FILE* myFile, InfoHeader header);
Image* open(char* myFile);
Image* convertToBin (int umbral, Image* myImage);
Image* readImg(char* name);
Image* convertToGray(Image* myImage);

void classification (int umbral ,Image* myImage);
void writeImg(int image, Image* myImage, int flag);
void response(char* image, Image* myImage, char* flag);
void freeImage (Image* myImage);

void pipelene (int quantityImages,int flag,int umbralClassification,int umbralImages,int quantityThread) ;

#endif