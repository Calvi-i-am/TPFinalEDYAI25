//Cabrera Alvaro, 2025.
//--------------------------

//Funciones de Hash auxiliares
//Definiciones de funciones de tabla, tanto de listas como de funciones

//--------------------------


#define MAX_SIZE_TABLA 100
#include <stdio.h>
#include "../Funciones/Funciones.h"


//Definicion del tipo "Hash"

typedef unsigned (*Hash)(char*, int);

/**
 * Funcion hash propuesta por Kenigan y Ritche en "The C
 * Programming Language", con la imagen acotada de [0,n-1]
 */
unsigned KRHashN(char *s, int n);

/**
 * Funcion hash para listas
 * Se usa en search para poder buscar listas 
 * en ListasVisitadas. Aun asi se agrega aqui 
 * porque es una funcion de hash.
 */
unsigned int ListHashN(Lista , int );

//NOTA: Las funciones que son de tablas de funciones contienen una F adelante
//Las que son de listas, una L.

typedef enum {T_Listas, T_Funciones} Tipo_Tabla;

typedef struct {
    Tipo_Tabla tipo;
    int cantidad;
    Hash FHash;
    void * elementos[MAX_SIZE_TABLA];
} Tabla_;

typedef Tabla_ * Tabla;

void * tabla_buscar(Tabla tabla, char * nombre);


void tabla_agregar_funcion(Tabla , char *, TipoFuncion, void*);

int tabla_full(Tabla);

Tabla tabla_crear();

void tabla_agregar_lista(Tabla tabla, Lista list);

void tabla_destruir(Tabla tabla);