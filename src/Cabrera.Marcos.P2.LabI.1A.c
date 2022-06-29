#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "utn.h"
#include "movies.h"
#include "Controller.h"
#include "LinkedList.h"

int main(void) {
	setbuf(stdout,NULL);
	srand(time(NULL));

	int option;
	char letra;
    int flagArchivo = 0;
    int flagRating = 0;
    int flagGenero = 0;
    int flagGuardar= 0;
	char path[20];

	LinkedList* listaPeliculas = ll_newLinkedList();
	if (listaPeliculas == NULL)
	{
		printf("No se pudo crear el linkedList\n");
		exit(1);
	}
	do{
		printf("\n  ___________________________\n");
		printf(" |         * MOVIES *        |\n");
		printf(" |___________________________|\n");
		printf(" | 1  | Cargar archivo       |\n");
		printf(" | 2  |	Imprimir lista       |\n");
		printf(" | 3  | Asignar rating       |\n");
		printf(" | 4  | Asignar genero       |\n");
		printf(" | 5  | Filtrar por genero   |\n");
		printf(" | 6  | Ordenar películas    |\n");
		printf(" | 7  | Guardar películas    |\n");
		printf(" | 8  | Salir                |\n");
		printf(" |---------------------------|\n");

		do{
			printf("  ___________________________________________");
			printf("\n | Por favor no ingrese letras, solo numeros |");
			printf("\n  __________________________");
			printf("\n | Introduzca una option: ");
			fflush(stdin);
			scanf("%d", &option);
			scanf("%c", &letra);
		} while ((isalpha(letra)) || (option < 1 || option >8));

		switch (option){
		case 1:
			if(flagArchivo == 0){
				utn_getNombre(path, 20, " |> Ingrese nombre del Archivo(sin .csv): ", "\n |> Error, Reingrese Nombre\n", 1);
				strcat(path,".csv"); // uso esta funcion para concatear '.CSV' al archivo, pq utn_getNombre no valida '.'
				while(!controller_loadFromText(path, listaPeliculas)){
					utn_getNombre(path, 20, " |> Ingrese nombre del Archivo(sin .csv): ", "\n |> Error, Reingrese Nombre\n", 1);
					strcat(path,".csv");
				}
				flagArchivo=1;
			}
			else{
				printf("\n   >> Ya esta cargado con exito!!!\n");
				printf(" _______________________________________\n");
			}
			break;

		case 2:
			if(flagArchivo!= 0 && controller_ListeMovies(listaPeliculas))
			{
				printf("\n   >> Se cargo con exito!!!\n");
				printf(" _______________________________________\n");
			}
			break;
		case 3:
			if(flagArchivo!= 0 && controller_rating(listaPeliculas))
			{
				flagRating = 1;
				printf("\n   >> Rating cargados con exito!!!\n");
				printf(" _______________________________________\n");

			}
			break;
		case 4:
			if(flagArchivo!= 0 && controller_genero(listaPeliculas))
			{
				flagGenero = 1;
				printf("\n   >> Genero cargados con exito!!!\n");
				printf(" _______________________________________\n");
			}
			break;
		case 5:
			if(flagArchivo!= 0 &&flagRating != 0 && flagGenero !=0)
			{
				controller_filterMovies(listaPeliculas);
			}
			break;
		case 6:
			if(flagArchivo!= 0 &&flagRating != 0 && flagGenero !=0)
			{
				controller_sortMovies(listaPeliculas);
			}
			break;
		case 7:
			if(flagArchivo!= 0 && controller_saveAsText("movies.csv",listaPeliculas))
			{
				flagGuardar = 1;
				printf("\n   >> Se guardo con exito!!!\n");
				printf(" _______________________________________\n");
			}
			break;
		case 8:
			if (flagGuardar != 1)
			{
				option = -1;
				printf("\n\n		>> GUARDE PARA SALIR!!!\n");
			}
		break;
		}
	}while((isalpha(letra)) || (option !=8) );
	return EXIT_SUCCESS;
}
