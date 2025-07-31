//Cabrera Alvaro, 2025
//--------------------------

//Implementacion de estructuras de funciones
//Declaracion de funciones implementadas en el .c

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <stdlib.h>
#include "../Listas/listas.h"

#define MAX_SIZE_NOMBRE 20
#define MAX_COMPOSICION 30

typedef Lista (*FuncionLista)(Lista);

typedef enum{
    f_primitiva,
    f_bandera,
    f_compuesta,
} TipoFuncion;

typedef struct Funcion_{
    char nombre[MAX_SIZE_NOMBRE];
    TipoFuncion Tipo;
    union{ //Uso union porque si es primitiva, no es composicion, y viceversa
        FuncionLista primitiva; //SOLO SI ES TIPO PRIMITIVA
        struct Funcion_ * subfunciones[MAX_COMPOSICION]; //SOLO SI ES TIPO COMPUESTA
    };
    int cantidad_subfunciones; //Cantidad de subfunciones que tiene la funcion compuesta
} _Funcion;

typedef _Funcion * Funcion;

Lista Oi(Lista);
Lista Od(Lista);
Lista Si(Lista);
Lista Sd(Lista);
Lista Di(Lista);
Lista Dd(Lista);


#endif // FUNCIONES_H