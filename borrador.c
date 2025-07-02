#include <stdlib.h>

typedef struct SNodo_{
    int dato;
    struct SNodo_ * sig;
} SNodo;

typedef struct {
    SNodo * primero;
    SNodo * ultimo;
} Lista_;

typedef Lista_ * Lista;

//LAS LISTAS VAN A REPRESENTARSE COMO STRINGS.

//FAQ
//Porq retornar Lista y no null?
//para search va a ser mas facil y tiene una mejor claridad



//NOTA
//lista == NULL : lista inexistente
//lista != NULL pero lista->primero == lista->ultimo == NULL : lista vacia

Lista Oi(Lista list){

    if (list == NULL) {
        list = malloc(sizeof(Lista_));
        //Ahora checkeo si no pude reservar espacio
        if (list == NULL){
            printf("la lista era vacia y no se pudo crear una.\n");
            return list;
        }
    }
    SNodo * Nodo0i = malloc(sizeof(SNodo));
    if (Nodo0i == NULL){
        printf("Espacio insuficiente para crear nodo.\n");
        return list;
    }

    Nodo0i->dato = 0;
    Nodo0i->sig = list->primero;

    list->primero = Nodo0i;

    if (list->ultimo == NULL) list->ultimo = Nodo0i;

    return list;
}

Lista Od(Lista list){

    if (list == NULL) {
        list = malloc(sizeof(Lista_));
        //Ahora checkeo si no pude reservar espacio
        if (list == NULL){
            printf("la lista era vacia y no se pudo crear una.\n");
            return list;
        }
    }
    
    SNodo * Nodo0d = malloc(sizeof(SNodo));
    if (Nodo0d == NULL){
        printf("Espacio insuficiente para crear nodo.\n");
        return list;
    }
    Nodo0d->dato = 0;
    Nodo0d->sig = NULL;

    if(list->primero == NULL) list->primero = Nodo0d;
    if(list->ultimo != NULL) list->ultimo->sig = Nodo0d;
    list->ultimo = Nodo0d;

    return list;
}

Lista Si(Lista list){
    if (list == NULL || list->primero == NULL) return list;

    list->primero->dato++;
    return list;
}

Lista Sd(Lista list){
    if (list == NULL || list->ultimo == NULL) return list;
    list->ultimo->dato++;
    return list;
}

Lista Di(Lista list){

    if (list == NULL || list->primero == NULL) return list;

    SNodo * temp = list->primero->sig;
    free(list->primero);
    list->primero = temp;
    return list;
}

Lista Dd(Lista list){

    if (list == NULL || list->primero == NULL) return list;

    SNodo * temp = list->primero;
    //me paro en el penultimo
    for(; temp->sig != NULL && temp->sig->sig != NULL; temp = temp->sig);
    free(list->ultimo);
    list->ultimo = temp->sig;
    list->ultimo->sig = NULL;
    return list;
}

//--------------------
//-

//imprimir cadenas,
//el output sera del tipo: [1,2,3] , sin espacios :)

void imprimir_lista(Lista list){
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