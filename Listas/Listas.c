//Cabrera Alvaro, 2025.
//--------------------------

// Implementacion de las listas como simplemente enlazadas
// Funciones de listas (crear, agregar nodo, imprimir, copiar, eliminar)


#include "listas.h"
#include <stdlib.h>

//--------------------

//Crea una lista vacia y la retorna

Lista lista_crear(){
    Lista list = malloc(sizeof(Lista_));
    if (list == NULL){
        printf("lista_crear : no se pudo crear la lista ");
        return NULL;
    }
    
    //Inicializamos los datos
    list->nombre[0] = '\0';
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

    if (list->primero == NULL) {
        list->primero = Node;
    } else if(list->ultimo != NULL){
        list->ultimo->sig = Node;
    }
    list->ultimo = Node;
    
    
}

//Imprime la lista en formato [elem1, elem2, ... , elemN]

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

//Copia una lista y retorna la copia

Lista lista_copiar(Lista list){
    if (list == NULL) return NULL;

    Lista nueva_lista = lista_crear();
    if (nueva_lista == NULL) return NULL;

    SNodo * actual = list->primero;
    while(actual != NULL){
        lista_add_nodo(nueva_lista, actual->dato);
        actual = actual->sig;
    }

    return nueva_lista;
}

//ELimina una lista y libera la memoria utilizada

void lista_eliminar(Lista list){
    if (list == NULL) return;

    SNodo * actual = list->primero;
    while(actual != NULL){
        SNodo * temp = actual;
        actual = actual->sig;
        free(temp);
    }

    free(list);
}

int lista_comparar(Lista l1, Lista l2){
    
    if (l1 == NULL || l2 == NULL) return 0;

    SNodo * nodo1 = l1->primero;
    SNodo * nodo2 = l2->primero;

    int Iguales = 1;
    while(nodo1 != NULL && nodo2 != NULL && Iguales){
        if (nodo1->dato != nodo2->dato) Iguales = 0; 
        else{
            nodo1 = nodo1->sig;
            nodo2 = nodo2->sig;
        }
    }
    
    return 1;
}