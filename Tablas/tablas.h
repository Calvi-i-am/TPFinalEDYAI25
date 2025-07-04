//Cabrera Alvaro, 2025.
//--------------------------

//Funciones de Hash auxiliares
//Definiciones de funciones de tabla, tanto de listas como de funciones

//--------------------------

#include <stdio.h>
#include <stdlib.h>
#include "../Funciones/Funciones.h"
#include "../Listas/listas.h"

//Definicion del tipo "Hash"

typedef unsigned (*Hash)(char*, int);

/**
 * Funcion hash propuesta por Kenigan y Ritche en "The C
 * Programming Language", con la imagen acotada de [0,n-1]
 */
unsigned KRHashN(char *s, int n);

tabla_agregar_primitiva(Tabla_Funciones *, char *, FuncionLista);