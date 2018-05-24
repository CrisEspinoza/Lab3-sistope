# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <unistd.h>

# include "../utils/menu.c"
# include "../utils/structs.h"
#include <pthread.h>

int main(int argc, char *argv[])
{
	/* code */
    int quantityImages;
    int umbralImages;
    int umbralClassification;
    int quantityThread;
    int flag = 0;
    int c;

    opterr = 0;

    if (argc < 10)
    {
      printf("La cantidad de parametros en menor a la solicitada \n");
      return 0;
    }


    if (argc > 10)
    {
      printf("La cantidad de parametros en mayor a la solicitada \n");
      return 0;
    }

    while ((c = getopt (argc, argv, "c:h:u:n:b")) != -1)
      switch (c)
        {
        case 'c':
          sscanf(optarg, "%d", &quantityImages);
          break;
        case 'h':
          sscanf(optarg, "%d", &quantityThread);
          break;
        case 'u':
          sscanf(optarg, "%d", &umbralImages);
          break;
        case 'n':
          sscanf(optarg, "%d", &umbralClassification);
          break;
        case 'b':
          flag = 1;
          break;
        case '?':
          if (optopt == 'c' || optopt == 'u' || optopt == 'n' || optopt == 'b' || optopt == 'h')
              fprintf (stderr, "Opcion -%c requiere un argumento.\n", optopt);
        default:
          abort ();
        }
    
    if ( quantityImages < 0  )
    {
      printf("Ingrese un numero positivo para la cantidad de imagenes que desea procesar\n");
    }
    
    if ( quantityThread < 0  )
    {
      printf("Ingrese un numero positivo para la cantidad de hebras que desea procesar\n");
    }

    if ( umbralImages <= 0 && umbralImages >= 255  )
    {
      printf("EL umbralImages (-u ) tiene que ser mayor a 0 y menor a 255\n");
      return 1;
    }

    if ( umbralClassification >= 100 && umbralClassification <= 0)
    {
      printf("La varible umbralClassification (-n ) tiene que ser mayor a 0 y menor a 100 \n");
      return 1;
    }

    menu(quantityImages,quantityThread,umbralImages,umbralClassification,flag);


  return 0;
	
}