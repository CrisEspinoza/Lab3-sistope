# include "../utils/structs.h"
# include <stdlib.h>
#include <pthread.h>

//Cabeceras de funciones

void pipeline (int quantityImages,int flag,int umbralClassification,int umbralImages,int quantityThread);
Thread* initThreads (Thread* thread , int quantityThread);
void showThreads(Thread* threads, int quantityThread);
void toPlanThredas () ;