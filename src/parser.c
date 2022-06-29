#include <stdio.h>
#include <stdlib.h>

#include "utn.h"
#include "movies.h"
#include "parser.h"
#include "LinkedList.h"

int parser_movieFromText(FILE* pFile , LinkedList* pArrayMovieslist)
{
	int todoOk = 0;
	int aux;
	char buffer[4][30];

	eMovies* pAuxMovie;
	if(pFile != NULL && pArrayMovieslist != NULL)
	{
		fscanf(pFile,"%[^,], %[^,], %[^,],%[^\n]\n",buffer[0], buffer[1], buffer[2], buffer[3]);
		while(!feof(pFile))
		{
			aux = fscanf(pFile,"%[^,], %[^,], %[^,],%[^\n]\n",buffer[0], buffer[1], buffer[2], buffer[3]);
			if(aux != 4)
			{
				break;
			}
			else
			{
				pAuxMovie = eMovies_newParametros(buffer[0], buffer[1], buffer[2], buffer[3]);
				if(pAuxMovie != NULL)
				{
					if(!ll_add(pArrayMovieslist, pAuxMovie))
					{
						todoOk = 1;
					}
					else
					{
						eMovies_delete(pAuxMovie);
						break;
					}
				}
			}
		}
	}
    return todoOk;
}
