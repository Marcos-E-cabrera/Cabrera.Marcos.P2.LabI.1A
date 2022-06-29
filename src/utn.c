#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "movies.h"
#include "Controller.h"
#include "LinkedList.h"
#include "parser.h"
#include "utn.h"

// STATIC INT
static int getsString(char* cadena, int longitud);
static int getInt( int *pResultado);
static int isNumerica( char* cadena, int limite);
static int isFloat(char* cadena);
static int getFloat(float* pResultado);
static int esNombre(char* cadena,int longitud);
static int getNombre(char* pResultado,int longitud);
static int esDescripcion(char* cadena,int longitud);
static int getDescripcion(char* pResultado, int longitud);
static int isCodigoVuelo(char* code, int limite);

// > Validaciones

int utn_validacionDosCaracteres (char* mensaje, char a, char b)
{
	char charIngresado;
	int retorno = -1;

	if (mensaje != NULL)
	{
		retorno = 0;
		printf(mensaje);
		charIngresado = toupper(getchar());
		while (charIngresado != a && charIngresado != b)
		{
			printf ("Ingrese una opcion valida (%c/%c): ", a, b);
			fflush (stdin);
			charIngresado = toupper(getchar());
		}
		if (charIngresado == a)
		{
			retorno = 1;
		}
	}
	return retorno;
}

int utn_validacionCaracter (char *mensaje, char caracter)
{
	char charIngresado;
	int retorno = -1;

	if (mensaje != NULL)
	{
		retorno = 0;
		printf(mensaje);
		fflush (stdin);
		charIngresado = toupper(getchar());
		while (charIngresado != caracter)
		{
			printf ("Caracter incorrecto. Ingrese %c para continuar: ", caracter);
			fflush (stdin);
			charIngresado = toupper(getchar());
		}
	}

	return retorno;
}

// > Entero

/**
* \brief Lee de stdin hasta que encuentra un '\n' o hasta que haya copiado en cadena
*		 un máximo de ' longitud - 1' caracteres .
* \param pResultado Puntero al espacio de memoria donde se copiara la cadena obtenida
* \param longitud Define el tamaño de cadena
* \return 0 = Ok, -1 = Error
*/
static int getsString(char* cadena, int longitud)
{
	int todoOk = -1;
	if (cadena != NULL && longitud > 0 && fgets(cadena,longitud,stdin) == cadena)
	{
		fflush (stdin);
		if (cadena[ strlen (cadena)-1] == '\n' )
		{
			cadena[ strlen (cadena)-1] = '\0' ;
		}

		todoOk = 0;
	}
	return todoOk;
}

/**
* \brief Verifica si la cadena ingresada es numerica
* \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
* \return 0 = Ok, -1 = Error
*/
static int getInt( int *pResultado)
{
	int todoOk = -1;
	char buffer[777];

	if (pResultado != NULL)
	{
		if( getsString(buffer, sizeof(buffer)) == 0 && isNumerica(buffer, sizeof(buffer)))
		{
			todoOk = 0;
			*pResultado = atoi(buffer); // la función “atoi” recibe una cadena y devuelve un valor del tipo int.
		}
	}
	return todoOk;
}

/**
* \brief Verifica si la cadena ingresada es numerica
* \param cadena Cadena de caracteres a ser analizada
* \return 0 = Ok, -1 = Error
*/
static int isNumerica( char* cadena, int limite)
{
	int todoOk = -1;
	int i = 0;

	if (cadena != NULL && strlen (cadena) > 0 && limite > 0)
	{
		for(i=0;i<limite && cadena[i] != '\0';i++)
		{
			if(i==0 && (cadena[i] == '+' || cadena[i] == '-'))
			{
				continue;
			}
			if(cadena[i] < '0'||cadena[i] > '9')
			{
				todoOk = 0;
				break;
			}
			//CONTINUE
		}
		//BREAK
	}
	return todoOk;
}

/**
 * \brief Solicita un numero al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Es el Puntero que va a ser cargado
 * \param mensaje Pide ingresar un numero
 * \param mensajeError Muestra un mesaje de error
 * \param minimo Limite minimo del numero
 * \param maximo Limite maximo del numero
 * \param reintento cuantas veces va a poder ingresar un numero
 * \return 0 = Ok, -1 = Error
 */
int utn_getNumero( int* pResultado, char * mensaje, char * mensajeError, int minimo, int maximo, int reintentos)
{
	int todoOk = -1;
	int bufferInt;

	do
	{
		printf("%s",mensaje);
		if(	getInt(&bufferInt) == 0 &&
			bufferInt >= minimo &&
			bufferInt <= maximo)
		{
			todoOk = 0;
			*pResultado = bufferInt;
			break;
		}
		printf("%s",mensajeError);
		reintentos--;
	}while(reintentos>=0);

	return todoOk;
}

// -- FLOTANTES

/**
* \brief Verifica si la cadena ingresada es decimal
* \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
* \return 0 = Ok, -1 = Error
*/
static int getFloat(float* pResultado)
{
	int todoOk = -1;
	char buffer[777];

	if (pResultado != NULL)
	{
		if( getsString(buffer, sizeof(buffer)) == 0 && isFloat(buffer) == 1)
		{
//			for( int i = 0 ; i < 8; i++)
//			{
//				printf("%d  %d  %c\n", i, buffer[i], buffer[i]);
//			}
//			printf("__________________\n");

			todoOk = 0;
			*pResultado = atof(buffer);
		}
	}
	return todoOk;
}

/**
* \brief Verifica si la cadena ingresada es decimal
* \param cadena Cadena de caracteres a ser analizada
* \return 0 = Ok, -1 = Error
*/
static int isFloat(char* cadena)
{
	int todoOk = 1;
	int i = 0;
	int contadorPuntos = 0;

	if(cadena != NULL && strlen(cadena) > 0)
	{
		for(i=0 ; cadena[i] != '\0'; i++)
		{
			if(i==0 && (cadena[i] == '-' || cadena[i] == '+'))
			{
				continue;
			}
			if(cadena[i] < '0' || cadena[i] > '9' )
			{
				if(cadena[i] == '.' && contadorPuntos == 0)
				{
					contadorPuntos++;
				}
				else
				{
					todoOk = 0;
					break;
				}
			}
		}
	}
	return todoOk;
}

/**
* \brief Solicita un numero flotante al usuario, luego de verificarlo devuelve el resultado
* \param pResultado Es el Puntero que va a ser cargado
* \param mensaje Pide ingresar un numero
* \param mensajeError Muestra un mesaje de error
* \param minimo Limite minimo del numero
* \param maximo Limite maximo del numero
* \param reintento cuantas veces va a poder ingresar un numero
* \return 0 = Ok, -1 = Error
*/
int utn_getFloat( float* pResultado, char * mensaje, char * mensajeError, float minimo, float maximo, int reintentos)
{
	int todoOk = -1;
	float bufferFloat;

	while(reintentos>0)
	{
		reintentos--;
		printf("%s",mensaje);
		if( getFloat(&bufferFloat) == 0)
		{
			if( bufferFloat >= minimo && bufferFloat <= maximo )
			{
				*pResultado = bufferFloat;
				todoOk = 0;
				break ;
			}
		}
		printf("%s", mensajeError);
	}
	return todoOk;
}

// -- CHAR

/**
 * \brief Obtiene un string valido como nombre
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorna 0 (EXITO) si se obtiene un numero flotante y -1 (ERROR) si no
 *
 */
static int getNombre(char* pResultado, int longitud)
{
    int retorno=-1;
    char buffer[4096];

    if(pResultado != NULL)
    {
    	if(	getsString(buffer,sizeof(buffer))==0 &&
    		esNombre(buffer,sizeof(buffer)) &&
			strnlen(buffer,sizeof(buffer))<longitud)
    	{
    		strncpy(pResultado,buffer,longitud);
			retorno = 0;
		}
    }
    return retorno;
}

/**
 * \brief Verifica si la cadena ingresada es un nombre valido
 * \param cadena Cadena de caracteres a ser analizada
 * \return Retorna 1 (verdadero) si la cadena es valida y 0 (falso) si no lo es
 *
 */
static int esNombre(char* cadena,int longitud)
{
	int i=0;
	int retorno = 1;

	if(cadena != NULL && longitud > 0)
	{
		for(i=0 ; cadena[i] != '\0' && i < longitud; i++)
		{
			if((cadena[i] < 'A' || cadena[i] > 'Z' ) && (cadena[i] < 'a' || cadena[i] > 'z' ))
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief Solicita un nombre al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param longitud Es la longitud del array resultado
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje de Error a ser mostrado
 * \param reintentos Cantidad de reintentos
 * \return Retorna 0 si se obtuvo el numero flotante y -1 si no
 *
 */
int utn_getNombre(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos)
{
	char bufferString[4096];
	int retorno = -1;
	while(reintentos>=0)
	{
		reintentos--;
		printf("%s",mensaje);
		if(getNombre(bufferString,sizeof(bufferString)) == 0 && strnlen(bufferString,sizeof(bufferString)) < longitud )
		{
			strncpy(pResultado,bufferString,longitud);
			retorno = 0;
			break;
		}
		printf("%s",mensajeError);
	}
	return retorno;
}

/**
 * \brief Obtiene un string valido como descripcion
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorna 0 (EXITO) si se obtiene un numero flotante y -1 (ERROR) si no
 *
 */
static int getDescripcion(char* pResultado, int longitud)
{
    int retorno=-1;
    char buffer[4096];

    if(pResultado != NULL)
    {
    	if(	getsString(buffer,sizeof(buffer))==0 &&
    		esDescripcion(buffer,sizeof(buffer)) &&
			strnlen(buffer,sizeof(buffer))<longitud)
    	{
    		strncpy(pResultado,buffer,longitud);
			retorno = 0;
		}
    }
    return retorno;
}

/**
 * \brief Verifica si la cadena ingresada es una descripcion valida
 * \param cadena Cadena de caracteres a ser analizada
 * \return Retorna 1 (verdadero) si la cadena es valida y 0 (falso) si no lo es
 *
 */
static int esDescripcion(char* cadena,int longitud)
{
	int i=0;
	int retorno = 1;

	if(cadena != NULL && longitud > 0)
	{
		for(i=0 ; cadena[i] != '\0' && i < longitud; i++)
		{
			if(cadena[i] != '.' && cadena[i] != ' ' && (cadena[i] < 'A' || cadena[i] > 'Z' ) && (cadena[i] < 'a' || cadena[i] > 'z' ) && (cadena[i] < '0' || cadena[i] > '9' ) )
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief Solicita una descripcion al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param longitud Es la longitud del array resultado
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje de Error a ser mostrado
 * \param reintentos Cantidad de reintentos
 * \return Retorna 0 si se obtuvo el numero flotante y -1 si no
 *
 */
int utn_getDescripcion(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos)
{
    char bufferString[4096];
    int retorno = -1;
    while(reintentos>=0)
    {
        reintentos--;
        printf("%s",mensaje);
        if(getDescripcion(bufferString,sizeof(bufferString)) == 0 && strnlen(bufferString,sizeof(bufferString)) < longitud )
        {
            strncpy(pResultado,bufferString,longitud);
            retorno = 0;
            break;
        }
        printf("%s",mensajeError);
    }
	return retorno;
}

static int isCodigoVuelo(char* code, int limite)
{
	int i=0;
	int todoOk = 1;

	if(code != NULL && limite > 0)
	{
		for(i=0 ; code[i] != '\0' && i < limite; i++)
		{
			if((code[i] < 'A' || code[i] > 'Z' ) && (code[i] < 'a' || code[i] > 'z' ) && (code[i] < '1' || code[i] > '9' ))
			{
				todoOk = 0;
				break;
			}
		}
	}
	return todoOk;
}

int utn_getCode(char* codigo,char* mensaje, char* mensajeError, int max, int reintentos)
{
	int todoOk = 1;
    char bufferString[max];

	while(reintentos>=0)
	{
		reintentos--;
		printf("%s",mensaje);
		if(getsString(bufferString,sizeof(bufferString)) == 0 && isCodigoVuelo(bufferString,sizeof(bufferString)))
        {
			strncpy(codigo,bufferString,max);
			todoOk = 0;
			break;
		}
		printf("%s",mensajeError);
	}
	return todoOk;
}
