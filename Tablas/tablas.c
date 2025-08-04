#include "tablas.h"



unsigned KRHashN(char *s, int n) {
  unsigned hashval;
  for (hashval = 0; *s != '\0'; ++s) {
    hashval = *s + 31 * hashval;
  }
  return hashval % n;
}

unsigned int ListHashN(Lista l, int n){

    if (l == NULL || l->primero == NULL) return 0;

    unsigned int hashval = 0;
    SNodo * actual = l->primero;

    while(actual != NULL){
        hashval += actual->dato; //Sumo el valor del nodo al hash
        actual = actual->sig; //Avanzo al siguiente nodo
    }

    //Retorno el hash modificado por n para evitar overflow
    return hashval % n;
}

int tabla_full(Tabla tabla){
    return (tabla->cantidad >= MAX_SIZE_TABLA);
}

void * tabla_buscar(Tabla tabla, char * nombre){
    int idx = tabla->FHash(nombre, MAX_SIZE_TABLA);
    int encontrado = 0;
    while(tabla->elementos[idx] != NULL && !(encontrado)){
        if (strcmp(((Funcion)tabla->elementos[idx])->nombre, nombre) == 0)
            encontrado = 1;
        else {
            idx = (idx + 1) % MAX_SIZE_TABLA; //linear probing simple
        }
    }
    if(encontrado)
        return tabla->elementos[idx];
    return NULL;
}



void tabla_agregar_funcion(Tabla tabla, char * nombre, TipoFuncion tipo,
void* f){

    if (tabla->tipo != T_Funciones) return; //checkeo que sea tabla de funciones

    Funcion  f_actual = NULL;

    if(tipo != f_compuesta){
        f_actual = malloc(sizeof(_Funcion));
        f_actual->Tipo = tipo;
        strcpy(f_actual->nombre, nombre);
        f_actual->cantidad_subfunciones = 0; //Inicializo cantidad de subfunciones a 0
        if (tipo == f_primitiva) f_actual->primitiva = (FuncionLista) f;
    }

    else{
        f_actual = (Funcion) f;
    }

    

    int idx = KRHashN(f_actual->nombre, MAX_SIZE_TABLA);
    for(int i = 1; tabla->elementos[idx] != NULL && !(tabla_full(tabla)); i++)
        idx = (idx + 1) % MAX_SIZE_TABLA; //linear probing simple

    tabla->elementos[idx] = f_actual;
    
    if (f_actual->Tipo != f_bandera) tabla->cantidad++;

}

void tabla_agregar_lista(Tabla tabla, Lista list){
    if (tabla->tipo != T_Listas) return;

    int idx = ListHashN(list->nombre, MAX_SIZE_TABLA);

    for(int i = 1; tabla->elementos[idx] != NULL && !(tabla_full(tabla)); i++)
        idx = (idx + 1) % MAX_SIZE_TABLA; //linear probing simple

    tabla->elementos[idx] = list;
    
    tabla->cantidad++;
}



Tabla tabla_crear(Tipo_Tabla tipo){
    Tabla  tabla = malloc(sizeof(Tabla_));
    tabla->cantidad = 0;
    tabla->FHash = KRHashN;
    for(int i = 0; i < MAX_SIZE_TABLA; i++) tabla->elementos[i] = NULL;

    tabla->tipo = tipo;

    if(tipo == T_Funciones){

    tabla_agregar_funcion(tabla,"Oi",f_primitiva,Oi);
    tabla_agregar_funcion(tabla,"Od",f_primitiva,Od);
    tabla_agregar_funcion(tabla,"Di",f_primitiva,Di);
    tabla_agregar_funcion(tabla,"Dd",f_primitiva,Dd);
    tabla_agregar_funcion(tabla,"Si",f_primitiva,Si);
    tabla_agregar_funcion(tabla,"Sd",f_primitiva,Sd);
    tabla_agregar_funcion(tabla,"<",f_bandera,NULL);
    tabla_agregar_funcion(tabla,">",f_bandera,NULL);

    }

    return tabla;
}

void tabla_destruir(Tabla tabla){
    if (tabla == NULL) return;

    for(int i = 0; i < MAX_SIZE_TABLA; i++){
        if (tabla->elementos[i] != NULL){
            if (tabla->tipo == T_Funciones) free(tabla->elementos[i]);
            else if (tabla->tipo == T_Listas) lista_eliminar((Lista) tabla->elementos[i]);
        }
    }
    free(tabla);
}