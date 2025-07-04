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

typedef struct TablaFunciones_{
    int cantidad;
    Hash FHash;
    Funcion * Funciones[MAX_SIZE_TABLA];
} TablaFunciones;

void tabla_agregar_primitiva(TablaFunciones *, char *, FuncionLista);

TablaFunciones * tabla_crear();