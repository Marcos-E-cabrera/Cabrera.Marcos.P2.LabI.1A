#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utn.h"
#include "movies.h"
#include "parser.h"
#include "Controller.h"
#include "LinkedList.h"

// > Mostrar
int eMovies_ImprimirDatos(eMovies* auxMovies)
{
	int todoOk = 0;
	int id_peli;
	char titulo[30];
	char genero[30];
	float rating;

	if(auxMovies!=NULL)
	{
		eMovies_getId_peli(auxMovies, &id_peli);
		eMovies_getTitulo(auxMovies, titulo);
		eMovies_getGenero(auxMovies, genero);
		eMovies_getRating(auxMovies, &rating);
        printf(" | %-3d | %-30s | %-30s |  %-.1f   |\n", id_peli,titulo,genero,rating);
		todoOk=1;
	}
	return todoOk;
}

// > Constructores
eMovies* eMovies_new()
{
	eMovies* auxMovies=(eMovies*) malloc(sizeof(eMovies));
	if(auxMovies != NULL)
	{
		auxMovies->id_peli= 0;
		strcpy(auxMovies->titulo,"*");
		strcpy(auxMovies->genero,"*");
		auxMovies->rating=0;
	}
	return auxMovies;
}

eMovies* eMovies_newParametros(char* id_peli,char* titulo, char* genro, char* rating)
{
	eMovies* newMovies;
	newMovies= eMovies_new();
    if(newMovies!=NULL)
    {
    	if(!(eMovies_setId_peli(newMovies, atoi(id_peli)) &&
    		 eMovies_setTitulo(newMovies, titulo) &&
			 eMovies_setGenero(newMovies, genro) &&
			 eMovies_setRating(newMovies, atof(rating))))
    	{
    		eMovies_delete(newMovies);
    		newMovies = NULL;
    	}
    }
	return newMovies;
}

// > Destucor
void eMovies_delete(eMovies* this)
{
	free (this);
}

// > Setters and Getters
// >> Id_peli
int eMovies_setId_peli(eMovies* this,int id_peli)
{
    int todoOk = 0;
    if(this != NULL && id_peli > 0)
    {
    	this->id_peli = id_peli;
        todoOk = 1;
    }
    return todoOk;
}

int eMovies_getId_peli(eMovies* this,int* id_peli)
{
	int todoOk = 0;
	if (this != NULL)
	{
		*id_peli = this -> id_peli;
		todoOk = 1;
	}
	return todoOk;
}

// >> Titulo
int eMovies_setTitulo(eMovies* this,char* titulo)
{
    int todoOk = 0;
    if(this != NULL && titulo != NULL && strlen(titulo) < 50 && strlen(titulo) > 2)
    {
        strcpy(this->titulo, titulo);
        strlwr(this->titulo);
        (this->titulo)[0] = toupper((this->titulo)[0]);
        todoOk = 1;
    }
    return todoOk;
}

int eMovies_getTitulo(eMovies* this,char* titulo)
{
    int todoOk = 0;
    if(this != NULL && titulo != NULL )
    {
        strcpy(titulo, this->titulo);
        todoOk = 1;
    }
    return todoOk;
}

// >> Genero
int eMovies_setGenero(eMovies* this,char* genero)
{
    int todoOk = 0;
    if(this != NULL && genero != NULL && strlen(genero) < 50 && strlen(genero) > 2)
    {
        strcpy(this->genero, genero);
        strlwr(this->genero);
        (this->genero)[0] = toupper((this->genero[0]));
        todoOk = 1;
    }
    return todoOk;
}

int eMovies_getGenero(eMovies* this,char* genero)
{
    int todoOk = 0;
    if(this != NULL && genero != NULL )
    {
        strcpy(genero, this->genero);
        todoOk = 1;
    }
    return todoOk;
}

// >> Rating
float eMovies_setRating(eMovies* this,float rating)
{
	int todoOk = 0;
	if(this != NULL && rating >= 0 && rating < 10)
	{
		this->rating = rating;
        todoOk = 1;
	}
	return todoOk;
}

float eMovies_getRating(eMovies* this,float* rating)
{
	int todoOk = 0;
	if (this != NULL)
	{
		*rating = this->rating;
		todoOk = 1;
	}
	return todoOk;
}

// >> Map
void* eMovies_asignarRating(void* auxMovies)
{
    int min=10;
    int max=100;
    float rating;

    eMovies* auxMovie;
    auxMovie = (eMovies*) auxMovies;

    if (auxMovies != NULL)
    {
        rating = (float) ((rand() % (max-min+1)) + min) / 10;

        if(rating > 0){
			eMovies_setRating(auxMovie, rating);
        }
    }
    return auxMovie;
}

void* eMovies_asignarGenero(void* auxMovies)
{
    int min=1;
    int max=4;
	int genero;

	eMovies* auxMovie = NULL;
    auxMovie = (eMovies*) auxMovies;

    if (auxMovies != NULL)
    {
    	genero = (float) ((rand() % (max-min+1)) + min);
        switch(genero){
        case 1:
            eMovies_setGenero(auxMovie, "drama");
        break;
        case 2:
            eMovies_setGenero(auxMovie, "comedia");
        break;
        case 3:
            eMovies_setGenero(auxMovie, "accion");
        break;
        case 4:
            eMovies_setGenero(auxMovie, "terror");
        break;
        }
    }
    return auxMovie;
}

// >> filter
int eMovies_filterDrama(void* a)
{
	int rta = 0;
	eMovies* pMovie = NULL;
	pMovie=(eMovies*) a;
	if(a != NULL){
		if(strcmp(pMovie->genero,"Drama") == 0)
		{
			rta = 1;
		}
	}
	return rta;
}

int eMovies_filterComedia(void* a){
	int rta = 0;
	eMovies* pMovie = NULL;
	pMovie=(eMovies*) a;
	if(a != NULL){
		if(strcmp(pMovie->genero,"Comedia")==0){
			rta = 1;
		}
	}
	return rta;
}

int eMovies_filterAccion(void* a){
	int rta = 0;
	eMovies* pMovie = NULL;
	pMovie=(eMovies*) a;
	if(a != NULL){
		if(strcmp(pMovie->genero,"Accion")==0){
			rta = 1;
		}
	}
	return rta;
}

int eMovies_filterTerror(void* a){
	int rta = 0;
	eMovies* pMovie = NULL;
	pMovie=(eMovies*) a;
	if(a != NULL){
		if(strcmp(pMovie->genero,"Terror")==0){
			rta = 1;
		}
	}
	return rta;
}

// >> sort
int eMovies_sortGeneroYRating(void*a , void*b)
{
	int rta =0;
    eMovies* movieA;
    eMovies* movieB;
    if( a != NULL && b != NULL)
    {
    	movieA = (eMovies*) a;
    	movieB = (eMovies*) b;
    	if( (strcmp(movieA->genero, movieB->genero) > 0) || ( (strcmp(movieA->genero, movieB->genero) == 0) && (movieA->rating < movieA->rating)) ){
    		rta=1;
    	}
    	else if( (strcmp(movieA->genero, movieB->genero) < 0) || ( (strcmp(movieA->genero, movieB->genero) == 0) && (movieA->rating > movieA->rating)) ){
    		rta=-1;
    	}
    }
    return rta;
}
