# include <stdio.h>
# include <stdlib.h>

# include "../utils/structs.h"
# include "../utils/bmplib.h"
# include "imagelib.c"
# include "functions.h"

#include <pthread.h>

// Variables globales 

Thread* threads = NULL;
Image* img = NULL;
int* threadsId = NULL;
int cantTheards = 0;

// Fin de variables globales

/* --------------------- Funciones que trabajaran a las hebras ------------------------------- */

/*
 * Funcion threads_show
 * Funcion que muestra por consola un arreglo de punteros de la estructura Thread_t.
 * @param Thread_t** threads:Arreglo de punteros de estructuras Thread_t.
*/
void showThreads(Thread* threads, int quantityThread)
{
     
    int i;

    for(i = 0; i <  quantityThread; i++)
    {
        printf("Hebra : %d - pos : %d , row: %d  - endrow : %d \n", 
            (i+1) ,threads[i].pos , threads[i].positions->row, threads[i].positions->endrow );
    }
    
}

Thread* initThreads (Thread* thread , int quantityThread)
{
    int i;

    thread = (Thread*)malloc(sizeof(Thread)*quantityThread);

    for (i = 0 ; i < quantityThread ; i++)
    {
        thread[i].positions = (Position*)malloc(sizeof(Position));
        thread[i].positions->row = 0;
        thread[i].positions->endrow = 0;
        thread[i].pos = i;
        thread[i].barrer = (pthread_barrier_t*) malloc(sizeof(pthread_barrier_t));
        pthread_barrier_init(&thread->barrer[i],NULL,quantityThread);
    }

    return thread;
}

void toPlanThredas () 
{
    int i, balance,rest,contThread = 0 ;
    printf("dimensiones de la matriz fila : %d , columna: %d -- cantidad de hebras : %d \n", img->height, img->width,cantTheards);

    if (cantTheards == img->height)
    {
        printf("Las filas de la matriz es igual a la cantidad de hebras \n");

        for (i = 0 ; i < cantTheards ; i++)
            {
                threads[i].positions->row = i;
                threads[i].positions->endrow = i;
            }
    }

    if (cantTheards < img->height)
    {
        printf("La cantidad de hebras es menor a las filas de la matriz \n");

        balance = img->height / cantTheards;  
        rest = img->height % cantTheards;

        printf("El equilibrio seria : %d y el resto : %d \n",  balance , rest);
        for (i = 0 ; i < img->height ; ++i)
        {
            printf("llegue aca \n");
            threads[contThread].positions->row = i;
            threads[contThread].positions->endrow = i + (balance - 1);
            if ( rest != 0  )
            {
                threads[contThread].positions->endrow++;
                rest--;
                i++;
            }
            i = i + ( balance - 1 );
            contThread++;
            printf("EL nuevo valor de i es : %d y hebra : %d \n" , i , contThread);
        }
    }

    if (cantTheards > img->height)
    {
        printf("La cantidad de hebras es mayor a las filas de la matriz \n");

        for (i = 0 ; i < cantTheards ; i++)
        {
            if (i < img->height)
            {
                threads[i].positions->row = i;
                threads[i].positions->endrow = i;
            }
            else
            {
                threads[i].positions->row = -1;
                threads[i].positions->endrow = -1;
            }
        }
    }

    printf("------------ Se termino proceso de la funcion parte 1 ----------\n");
}

void* functions(void* idThread)
{
    int idT = *(int*)idThread;
    printf("%d\n", idT );

    if ( idT == 0  )
    {
        printf("la hebra %d leyo la imagen \n", idT );
        img = readImg("1");
    }

    pthread_barrier_wait(threads[0].barrer);

    // Planificando hebras 
    if (idT == 0 )
    {
        toPlanThredas();
    } 
    // hebras ya planificadas
    pthread_barrier_wait(threads[0].barrer);

    

    
    pthread_exit (NULL);
}


void pipeline (int quantityImages,int flag,int umbralClassification,int umbralImages,int quantityThread) 
{

    printf("Llegue aca \n");

    // Inicializar estructura de hebras y planificarlas 
    cantTheards = quantityThread; // Realizamos la asignación de la cantidad de hebras totales
    threads = initThreads(threads,quantityThread);
    threadsId = (int*) malloc(sizeof(int)*quantityThread);
    showThreads(threads,quantityThread);
    //Inicilizando hebras

    //Iniciar hebras 
    int i;
    for(i = 0 ; i < quantityThread ; i++)
    {
        threadsId[i]=i;
        pthread_create(&threads[i].thread,NULL,functions,(void*)&threadsId[i]);
    }

    //Esperando hebras 
    for(i = 0 ; i < quantityThread ;i++)
    {
        pthread_join(threads[i].thread,NULL);
    }

    //showThreads(threads,quantityThread);

}
