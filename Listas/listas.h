//Cabrera Alvaro, 2025.
//--------------------------

//- Implementacion de las listas como simplemente enlazadas
//- Declaracion de funciones sobre listas

//--------------------------

//Listas

//Las listas seran representadas como una lista simplemente enlazada

#include <stdlib.h>

typedef struct SNodo_{
    int dato;
    struct SNodo_ * sig;
} SNodo;

typedef struct {
    SNodo * primero;
    SNodo * ultimo;
    char * EnCadena; //Esto seria la lista tipo string
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

/**
 * Imprime la lista, de forma: [n1,n2,n3,...,nj]
 */
void lista_imprimir(Lista);