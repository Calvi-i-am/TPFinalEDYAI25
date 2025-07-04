//Cabrera Alvaro, 2025.
//--------------------------

//- Implementacion de las listas como simplemente enlazadas
//- Funcion para imprimir listas

//--------------------------

//Listas

//Las listas seran representadas como una lista simplemente enlazada
#include <listas.h>
#include <stdlib.h>


//NOTA
//lista == NULL : lista inexistente
//lista != NULL pero lista->primero == lista->ultimo == NULL : lista vacia

//--------------------


//Crear lista

Lista defl(char * cadena){
    Lista list = lista_crear();
}

Lista lista_crear(){
    Lista  list = malloc(sizeof(Lista_));
    if (list == NULL){
        printf("lista_crear : no se pudo crear la lista ");
        return NULL;
    }

    list->primero = NULL;
    list->ultimo = NULL;
    return list;
}

//Agrega nodo a la lista

void lista_add_nodo(Lista list, int dato){
    //Si la lista es nula, se crea una lista vacia
    if (list == NULL){
        list = lista_crear();
        if (list == NULL){
            printf("lista_add_nodo : memoria insuficiente (nueva lista)");
            return;
        }
    }

    SNodo * Node = malloc(sizeof(SNodo));
    if(Node == NULL){
        printf("lista_add_nodo : memoria insuficiente (nodo)");
        return;
    }
    
    Node->dato = dato;
    Node->sig = NULL;

    if (list->primero == NULL) list->primero == Node;
    list->ultimo->sig = Node;
    list->ultimo = Node;
    
    
}

//imprimir cadenas,
//el output sera del tipo: [1,2,3] , sin espacios :)

void lista_imprimir(Lista list){
    if (list == NULL || list->primero == NULL){
        printf("lista vacia.\n");
        return;
    }

    printf("[");
    for(SNodo * temp = list->primero; temp != NULL; temp = temp->sig){
        printf("%d", temp->dato);
        if (temp->sig != NULL) printf(",");
    }
    
    printf("]\n");
}

//Transformar lista a string
//Para que? para search

char * lista_to_string(Lista list){
    
}