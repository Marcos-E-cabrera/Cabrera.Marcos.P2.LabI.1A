#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "utn.h"
#include "movies.h"
#include "parser.h"
#include "Controller.h"
#include "LinkedList.h"

// >>> Archivo.csv
int controller_loadFromText(char* path, LinkedList* pArrayListeMovies)
{
	int todoOk=0;
	FILE* pFile;

	if(pArrayListeMovies!=NULL)
	{
		pFile= fopen(path,"r");
		if(pFile!=NULL)
		{
			parser_movieFromText(pFile,pArrayListeMovies);
			printf("\n    >> Archivo cargado con exito!!!!\n");
			printf(" _______________________________________\n");
			todoOk=1;
		}
		fclose(pFile);
	}
    return todoOk;
}

int controller_ListeMovies(LinkedList* pArrayListeMovies)
{
	int todoOk=0;
	int tam;
	eMovies* pAuxMovie = NULL;
	if(pArrayListeMovies!=NULL)
	{
		tam=ll_len(pArrayListeMovies);
		if(tam>0)
		{
			todoOk=1;
			printf("                               >>> MOVIES LIST\n");
			printf("  ________________________________________________________________________________\n");
			printf(" | ID  |            TITULO              |              GENERO            | RATING |\n");
			printf(" |--------------------------------------------------------------------------------|\n");
			for(int i=0; i<tam; i++)
			{
				pAuxMovie = (eMovies*) ll_get(pArrayListeMovies,i);
				if(pAuxMovie != NULL)
				{
					eMovies_ImprimirDatos(pAuxMovie);
				}
			}
			printf(" |--------------------------------------------------------------------------------|\n");
		}
	}
	else
	{
		eMovies_delete(pAuxMovie);
	}
	return todoOk;
}

// >>> MAP
int controller_rating(LinkedList* pArrayListeMovies)
{
    int todoOk = 0;
    if(pArrayListeMovies != NULL)
    {
    	if(ll_map(pArrayListeMovies, eMovies_asignarRating)!=NULL){
			controller_ListeMovies(pArrayListeMovies);
			todoOk = 1;
    	}
    }
    return todoOk;
}

int controller_genero(LinkedList* pArrayListeMovies)
{
    int todoOk = 0;
    if(pArrayListeMovies != NULL && ll_map(pArrayListeMovies, eMovies_asignarGenero)!=NULL)
    {
    	controller_ListeMovies(pArrayListeMovies);
        todoOk = 1;
    }
    return todoOk;
}

// >>> FILTER
int controller_filterMovies(LinkedList* pArrayListeMovies)
{
    int todoOk = 0;
    int genero;
    if (pArrayListeMovies != NULL)
    {
    	utn_getNumero(&genero," \n    >>> FILTRAR POR:\n"
    						  "  ________________________\n"
    			              " | 1  | Drama.            |\n"
    						  " | 2  | Comedia.          |\n"
    			              " | 3  | Accion.           |\n"
    						  " | 4  | Terror.           |\n"
    						  " |------------------------|\n"
  							  " |> Ingrese Filtro: " , " |> Ingrese un Filtro valido\n", 1, 4, 10);
        switch(genero)
        {
        case 1:
        	controller_filterDrama(pArrayListeMovies);
            todoOk = 1;
            break;
        case 2:
        	controller_filterComedia(pArrayListeMovies);
            todoOk = 1;
            break;
        case 3:
        	controller_filterAccion(pArrayListeMovies);
            todoOk = 1;
            break;
        case 4:
        	controller_filterTerror(pArrayListeMovies);
            todoOk = 1;
        	break;
        }
    }
    return todoOk;
}

int controller_filterDrama(LinkedList* pArrayListeMovies)
{
	int todoOk=0;

	if(pArrayListeMovies!=NULL)
	{
		pArrayListeMovies =ll_filter(pArrayListeMovies, eMovies_filterDrama);
        controller_ListeMovies(pArrayListeMovies);
        printf("\n   >> Filtrado con exito!!!\n");
        printf(" _______________________________________\n");
        controller_saveAsText("moviesDrama.csv", pArrayListeMovies);
        todoOk = 1;
	}
	return todoOk;
}

int controller_filterComedia(LinkedList* pArrayListeMovies)
{
	int todoOk=0;

	if(pArrayListeMovies!=NULL)
	{
		pArrayListeMovies =ll_filter(pArrayListeMovies, eMovies_filterComedia);
        controller_ListeMovies(pArrayListeMovies);
        printf("\n   >> Filtrado con exito!!!\n");
        printf(" _______________________________________\n");
        controller_saveAsText("moviesComedia.csv", pArrayListeMovies);
        todoOk = 1;
	}
	return todoOk;
}

int controller_filterAccion(LinkedList* pArrayListeMovies)
{
	int todoOk=0;

	if(pArrayListeMovies!=NULL)
	{
		pArrayListeMovies =ll_filter(pArrayListeMovies, eMovies_filterAccion);
        controller_ListeMovies(pArrayListeMovies);
        printf("\n   >> Filtrado con exito!!!\n");
        printf(" _______________________________________\n");
        controller_saveAsText("moviesAccion.csv", pArrayListeMovies);
        todoOk = 1;
	}
	return todoOk;
}

int controller_filterTerror(LinkedList* pArrayListeMovies)
{
	int todoOk=0;

	if(pArrayListeMovies!=NULL)
	{
		pArrayListeMovies =ll_filter(pArrayListeMovies, eMovies_filterTerror);
        controller_ListeMovies(pArrayListeMovies);
        printf("\n   >> Filtrado con exito!!!\n");
        printf(" _______________________________________\n");
        controller_saveAsText("moviesTerror.csv", pArrayListeMovies);
        todoOk = 1;
	}
	return todoOk;
}

// >>> SORT
int controller_sortMovies(LinkedList* pArrayListeMovies)
{
    int todoOk = 0;
    if (pArrayListeMovies != NULL)
    {
        ll_sort(pArrayListeMovies, eMovies_sortGeneroYRating, 0);
        controller_ListeMovies(pArrayListeMovies);
        printf("\n   >> Ordenado con exito!!!\n");
        printf(" _______________________________________\n");
        todoOk = 1;
    }
    return todoOk;
}

// >>> Guardar csv
int controller_saveAsText(char* path , LinkedList* pArrayListeMovies)
{
	int todoOk=0;
	int tam;
	int id_peli;
	char titulo[30];
	char genero[30];
	float raitng;

	eMovies* pAuxMovie = NULL;
	FILE* pFile;
	if(path!=NULL && pArrayListeMovies!=NULL)
	{
		pFile=fopen(path,"w");
		if(pFile!=NULL)
		{
			tam = ll_len(pArrayListeMovies);

			fprintf(pFile,"id_peli,titulo,genero,duracion\n");

			for(int i=0; i<tam;i++)
			{
				pAuxMovie= (eMovies*) ll_get (pArrayListeMovies,i);
				if(pAuxMovie!=NULL)
				{
					todoOk=1;
					eMovies_getId_peli(pAuxMovie, &id_peli);
					eMovies_getTitulo(pAuxMovie, titulo);
					eMovies_getGenero(pAuxMovie, genero);
					eMovies_getRating(pAuxMovie, &raitng);
					fprintf(pFile,"%d,%s,%s,%.1f\n",id_peli,titulo,genero,raitng);
				}
			}
		}
		fclose(pFile);
	}
	return todoOk;
}
