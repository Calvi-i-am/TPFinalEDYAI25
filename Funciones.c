#include "listas.h"
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
//Cabrera Alvaro, 2025
//--------------------------

//Implementacion de las funciones primivitas
//Estructura y implementacion de funciones compuestas y recursivas


//FAQ
//Porq retornar Lista y no null?
//para search va a ser mas facil y tiene una mejor claridad


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

//--------------------------

//Definicion del tipo "Hash"

typedef unsigned (*Hash)(char*, int);

//Funcion para tablas hash con strings propuesta por
//Kernigan y Ritchie, pero modificada para que el resultado caiga 
// entre 0 y n-1

unsigned KRHashN(char *s, int n) {
  unsigned hashval;
  for (hashval = 0; *s != '\0'; ++s) {
    hashval = *s + 31 * hashval;
  }
  return hashval % n;
}

//-------------------------

#define MAX_SIZE_NOMBRE 20
#define MAX_COMPOSICION 30
#define MAX_SIZE_TABLA 100

typedef Lista (* FuncionLista)(Lista);


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

typedef struct TablaFunciones_{
    int cantidad;
    Hash FHash;
    Funcion * Funciones[MAX_SIZE_TABLA];
} TablaFunciones;

int tabla_full(TablaFunciones * tabla){
    return (tabla->cantidad >= MAX_SIZE_TABLA);
}

void tabla_agregar_primitiva(TablaFunciones * tabla, char * nombre,
FuncionLista f){

    Funcion * PRIMITIVA = malloc(sizeof(Funcion));
    strcpy(PRIMITIVA->nombre,nombre);
    PRIMITIVA->Tipo = F_PRIMITIVA;
    PRIMITIVA->primitiva = f;

    int idx = KRHashN(nombre, MAX_SIZE_TABLA);
    for(int i = 1; tabla->Funciones[idx] != NULL && !(tabla_full(tabla)); i++)
        idx = (idx + 1) % MAX_SIZE_TABLA; //linear probing simple

    tabla->Funciones[idx] = PRIMITIVA;
    
    tabla->cantidad++;
    
     }

TablaFunciones * tabla_crear(){
    TablaFunciones * tabla = malloc(sizeof(TablaFunciones));
    tabla->cantidad = 0;
    tabla->FHash = KRHashN;
    for(int i = 0; i < MAX_SIZE_TABLA; i++) tabla->Funciones[i] = NULL;

    tabla_agregar_primitiva(tabla,"0i",Oi);
    tabla_agregar_primitiva(tabla,"0d",Od);
    tabla_agregar_primitiva(tabla,"Si",Si);
    tabla_agregar_primitiva(tabla,"Sd",Sd);
    tabla_agregar_primitiva(tabla,"Di",Di);
    tabla_agregar_primitiva(tabla,"Dd",Dd);

    return tabla;
}





int main() {
    TablaFunciones *tabla = tabla_crear();  // crea y carga las primitivas

    printf("Contenido de la tabla hash:\n");
    printf("--------------------------------\n");

    for (int i = 0; i < MAX_SIZE_TABLA; i++) {
        printf("Índice %3d: ", i);
        if (tabla->Funciones[i] != NULL) {
            Funcion *f = tabla->Funciones[i];
            printf("%s (%s)\n",
                f->nombre,
                f->Tipo == F_PRIMITIVA ? "PRIMITIVA" :
                f->Tipo == F_COMPUESTA ? "COMPUESTA" : "RECURSIVA"
            );
        } else {
            printf("vacío\n");
        }
    }

    return 0;
}