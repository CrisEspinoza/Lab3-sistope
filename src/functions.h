# include "../utils/structs.h"
# include <stdlib.h>
#include <pthread.h>

//Cabeceras de funciones

void pipeline (int quantityImages,int flag,int umbralClassification,int umbralImages,int quantityThread);
Thread* initThreads (Thread* thread , int quantityThread);
void showThreads(Thread* threads, int quantityThread);
void toPlanThredas();
void verMatriz (Image* img);
void classification (Image* myImage,int inicio, int final) ;
void response(int image, Image* myImage, int flag, int umbral);
void freeImage (Image* myImage);