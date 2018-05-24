# include <stdio.h>
# include <stdlib.h>

# include "../utils/structs.h"
# include "../utils/bmplib.c"

#include <pthread.h>

/*
Entrada: Enteros que representan la anchura y altura de la imagen.
Descripción: Reserva memoria para la representación de una imagen.
Salida: Estructura Image con memoria reservada.
*/
Image* initImage(int height, int width)
{
	Image* myImage = (Image*)malloc(sizeof(Image));
 	myImage->height = height;
 	myImage->width = width;
 	myImage->isNearlyBlack = -1;
 	myImage->matrix = (Pixel**) malloc(sizeof(Pixel*) * height);
 	if(!myImage->matrix)
 	{
 		perror("## NO HAY SUFICIENTE MEMORIA PARA LA ASIGNACION ##");
		exit(0);
 	}
 	int i;
 	for (i = 0; i < height; i++)
 	{
 		myImage->matrix[i] = (Pixel*)malloc(width * sizeof(Pixel));
 		if(!myImage->matrix[i])
 		{
 			perror("## NO HAY SUFICIENTE MEMORIA PARA LA ASIGNACION ##");
			exit(0);
 		}
 	}
 	return myImage;
}
/*
Entrada: Archivo y dimensiones de la imagen.
Descripción: Se pide memoria para la imagen, posteriormente se almacenan en una matriz los valores RGB de cada pixel.
Salida: Estructura Image con matriz de pixeles listos.
*/
Image* loadImage(FILE* myFile, InfoHeader header)
{
 	int i, j;
 	int height = header.height;
 	int width = header.width;
 	Image* myImage = initImage(height, width);
 	myImage->header = header;
 	Pixel myPixel;
 	for(i = 0; i < myImage->height; i++)
 		for(j = 0; j < myImage->width; j++)
 		{
 			fread(&myPixel.red, sizeof(char), 1, myFile);
 			fread(&myPixel.green, sizeof(char), 1, myFile);
 			fread(&myPixel.blue, sizeof(char), 1, myFile);
 			if(myImage->header.bpp == 32)
 				fread(&myPixel.alpha, sizeof(char), 1, myFile);
 			myImage->matrix[i][j] = myPixel; 			
 		}
 	return myImage;
}
/*
Entrada: Nombre de un fichero.
Descripción: Abre un archivo. Luego hace llamado a funciones que reservan memoria y almacenan la imagen.
Salida: Estructura Image con todos sus valores almacenados.
*/
Image* open(char* myFile)
{
 	FILE* file = fopen(myFile, "rb"); // Abrir el archivo en modo binario
	if(!file)
		perror("No se puede abrir la imagen");
	InfoHeader infoh = readInfoHeader(file);
	Image* myImage = loadImage(file, infoh);
	fclose(file);
	return myImage;
}

/* 1. Lectura de imagen RGB
Entrada: Nombre del archivo
Descripción: Abre la imagen, repleta la matriz RGB y almacena header.
Salida: Estructura Image con todos sus valores correspondientes.
*/
Image* readImg(char* name)
{
	char* route = (char*)calloc(60, sizeof(char));
	strcat(route, "../images/imagen_");
	strcat(route, name);
    strcat(route, ".bmp");
    Image* img = open(route);
    //printf("Termine de leer la imagen \n");
	return img;
}

/* 2. Conversión a imagen en escala de grises
Entrada: Entra una imagen
Descripción: Convierto los componentes de la imagen a escala de grises 
Salida: Imagen en escala de grises
*/
Image* convertToGray(Image* myImage, int inicio, int final)
{
	int tmp, i, j;
	if (inicio != -1 )
	{
		//printf("entre aca: %d \n", inicio );
		for (i = inicio; i <= final; i++)
			for (j = 0; j < myImage->width; j++)
			{
				//printf("Entre aca \n");
				// Y = R ∗ 0.3 + G ∗ 0.59 + B ∗ 0.11
				tmp = myImage->matrix[i][j].red * 0.3 + myImage->matrix[i][j].green * 0.59 + myImage->matrix[i][j].blue * 0.11;
				myImage->matrix[i][j].red = tmp;
				myImage->matrix[i][j].green = tmp;
				myImage->matrix[i][j].blue = tmp;
			}
	}
	return myImage;
}

/* 3. Binarización de imagen
Entrada: Entra el umbral ingresado por pantalla y una imagen 
Descripción: Convierte los pixeles segun una clasificación ingresada por pantalla y revisa si le corresponde 0 o 255
Salida: Entraga la imagen con sus pixeles modificados
*/
Image* convertToBin (int umbral, Image* myImage, int inicio, int final)
{
	int i,j;
	if (inicio != -1)
	{
		for (i = inicio; i <= final; i++)
		{
			for (j = 0; j < myImage->width; j++)
			{
				if (myImage->matrix[i][j].red > umbral)
				{
					myImage->matrix[i][j].red = 255;
					myImage->matrix[i][j].blue = 255;
					myImage->matrix[i][j].green = 255;
				}
				else
				{
					myImage->matrix[i][j].red = 0;
					myImage->matrix[i][j].blue = 0;
					myImage->matrix[i][j].green = 0;
				}
			}
		}
	}
	return myImage;
}
