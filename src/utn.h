#ifndef UTN_H_
#define UTN_H_

// > Validaciones
int utn_validacionDosCaracteres (char* mensaje, char a, char b);
int utn_validacionCaracter (char *mensaje, char caracter);

// > Entero
int utn_getNumero( int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos);

// > Flotante
int utn_getFloat( float* pResultado, char * mensaje, char * mensajeError, float minimo, float maximo, int reintentos);

// > CHAR
int utn_getNombre(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos);
int utn_getDescripcion(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos);
int utn_getCode(char* codigo,char* mensaje, char* mensajeError, int max, int reintentos);

#endif /* UTN_H_ */

