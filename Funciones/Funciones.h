//Cabrera Alvaro, 2025
//--------------------------

//Implementacion de estructuras de funciones
//Declaracion de funciones implementadas en el .c

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE_NOMBRE 20
#define MAX_COMPOSICION 30
#define MAX_SIZE_TABLA 100

typedef Lista (*FuncionLista)(Lista);


typedef enum{
    F_PRIMITIVA,
    F_COMPUESTA,
    F_RECURSIVA,
} TipoFuncion;

typedef struct Funcion_{
    char nombre[MAX_SIZE_NOMBRE];
    TipoFuncion Tipo;
    union{ //Uso union porque si es primitiva, no es composicion, y viceversa
        FuncionLista primitiva; //SOLO SI ES TIPO PRIMITIVA
        struct Funcion_ * subfunciones[MAX_COMPOSICION];
    };
} Funcion;



Lista Oi(Lista);
Lista Od(Lista);
Lista Si(Lista);
Lista Sd(Lista);
Lista Di(Lista);
Lista Dd(Lista);