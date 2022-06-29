#ifndef MOVIES_H_
#define MOVIES_H_

typedef struct
{
	int id_peli;
	char titulo[50];
	char genero[50];
	float rating;
}eMovies;

// > Mostrar
int eMovies_ImprimirDatos(eMovies* auxMovies);

// > Constructores
eMovies* eMovies_new();
eMovies* eMovies_newParametros(char* id_peli,char* titulo, char* genro, char* rating);

// > Destructores
void eMovies_delete(eMovies* this);

// > Setters y Getters

// >> Id_peli
int eMovies_setId_peli(eMovies* this,int id_peli);
int eMovies_getId_peli(eMovies* this,int* id_peli);

// >> Titulo
int eMovies_setTitulo(eMovies* this,char* titulo);
int eMovies_getTitulo(eMovies* this,char* titulo);

// >> Genero
int eMovies_setGenero(eMovies* this,char* genero);
int eMovies_getGenero(eMovies* this,char* genero);

// >> Rating
float eMovies_setRating(eMovies* this,float rating);
float eMovies_getRating(eMovies* this,float* rating);

// >> Map
void* eMovies_asignarRating(void* auxMovies);
void* eMovies_asignarGenero(void* auxMovies);

// >> Filter
int eMovies_filterDrama(void* a);
int eMovies_filterComedia(void* a);
int eMovies_filterAccion(void* a);
int eMovies_filterTerror(void* a);

// >> sort
int eMovies_sortGeneroYRating(void*a , void*b);

#endif /* MOVIES_H_ */
