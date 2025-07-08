//Cabrera Alvaro, 2025.
//--------------------------

//Funciones de Hash auxiliares
//Definiciones de funciones de tabla, tanto de listas como de funciones

//--------------------------


#include "../Funciones/Funciones.h"
#include "../Listas/listas.h"

//Definicion del tipo "Hash"

typedef unsigned (*Hash)(char*, int);

/**
 * Funcion hash propuesta por Kenigan y Ritche en "The C
 * Programming Language", con la imagen acotada de [0,n-1]
 */
unsigned KRHashN(char *s, int n);

//NOTA: Las funciones que son de tablas de funciones contienen una F adelante
//Las que son de listas, una L.

typedef enum {T_Listas, T_Funciones} Tipo_Tabla;

typedef struct Tabla_{
    Tipo_Tabla tipo;
    int cantidad;
    Hash FHash;
    void * elementos[MAX_SIZE_TABLA];
} Tabla;

void tabla_agregar_primitiva(Tabla *, char *, FuncionLista);

Tabla * tabla_crear();

