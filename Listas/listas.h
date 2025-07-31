
//Cabrera Alvaro, 2025.
//--------------------------

// Implementacion de las listas como simplemente enlazadas
// Declaracion de funciones sobre listas



#ifndef LISTAS_H
#define LISTAS_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_NOMBRE_LISTA 30

typedef struct SNodo_{
    int dato;
    struct SNodo_ * sig;
} SNodo;

typedef struct {
    char nombre[MAX_NOMBRE_LISTA];
    SNodo * primero;
    SNodo * ultimo;
} Lista_;

typedef Lista_ * Lista;


//NOTA
//lista == NULL : lista inexistente
//lista != NULL pero lista->primero == lista->ultimo == NULL : lista vacia

//--------------------

/**
 * Crea una lista vacia
 */
Lista lista_crear();

/**
 * Crea un nodo y lo anade a la lista dada
 */
void lista_add_nodo(Lista,int);

/*
 * Imprime la lista, de forma: [elem1, elem2, ... , elemN]
 */
void lista_imprimir(Lista);

/**
 * Copia una lista y retorna la copia.
 */
Lista lista_copiar(Lista);

/**
 * Elimina la lista y libera toda su memoria
 */
void lista_eliminar(Lista);


#endif // LISTAS_H
