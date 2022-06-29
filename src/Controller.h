#include "LinkedList.h"

int controller_loadFromText(char* path,LinkedList* pArrayListeMovies);

int controller_ListeMovies(LinkedList* pArrayListeMovies);

int controller_rating(LinkedList* pArrayListeMovies);
int controller_genero(LinkedList* pArrayListeMovies);

int controller_filterMovies(LinkedList* pArrayListeMovies);

int controller_filterDrama(LinkedList* pArrayListeMovies);
int controller_filterComedia(LinkedList* pArrayListeMovies);
int controller_filterAccion(LinkedList* pArrayListeMovies);
int controller_filterTerror(LinkedList* pArrayListeMovies);

int controller_sortMovies(LinkedList* pArrayListeMovies);

int controller_saveAsText(char* path , LinkedList* pArrayListeMovies);
