#include "tablas.h"



unsigned KRHashN(char *s, int n) {
  unsigned hashval;
  for (hashval = 0; *s != '\0'; ++s) {
    hashval = *s + 31 * hashval;
  }
  return hashval % n;
}



int tabla_full(Tabla tabla){
    return (tabla->cantidad >= MAX_SIZE_TABLA);
}

void tabla_agregar_lista(Tabla tabla, Lista list){

    if(tabla->tipo != T_Listas) return;

    int idx = tabla->FHash(list->nombre,tabla->cantidad);
    for(int i = 1; tabla->elementos[idx] != NULL && !(tabla_full(tabla)); i++)
        idx = (idx + 1) % MAX_SIZE_TABLA;

    tabla->elementos[idx] = list;

}

void tabla_agregar_funcion(Tabla tabla, char * nombre, TipoFuncion tipo,
void* f){

    if (tabla->tipo != T_Funciones) return; //checkeo que sea tabla de funciones

    Funcion  f_actual = NULL;

    if(tipo != F_COMPUESTA){
        f_actual = malloc(sizeof(Funcion));
        f_actual->Tipo = tipo;
        strcpy(f_actual->nombre, nombre);
        if (tipo == F_PRIMITIVA) f_actual->primitiva = (FuncionLista) f;
    }

    else{
        f_actual = (Funcion) f;
    }

    

    int idx = KRHashN(f_actual->nombre, MAX_SIZE_TABLA);
    for(int i = 1; tabla->elementos[idx] != NULL && !(tabla_full(tabla)); i++)
        idx = (idx + 1) % MAX_SIZE_TABLA; //linear probing simple

    tabla->elementos[idx] = f_actual;
    
    tabla->cantidad++;

}

void tabla_agregar_lista(Tabla tabla, Lista list){
    if (tabla->tipo != T_Listas) return;

    int idx = KRHashN(list->nombre, MAX_SIZE_TABLA);

    for(int i = 1; tabla->elementos[idx] != NULL && !(tabla_full(tabla)); i++)
        idx = (idx + 1) % MAX_SIZE_TABLA; //linear probing simple

    tabla->elementos[idx] = list;
    
    tabla->cantidad++;
}



Tabla tabla_crear(Tipo_Tabla tipo){
    Tabla  tabla = malloc(sizeof(Tabla));
    tabla->cantidad = 0;
    tabla->FHash = KRHashN;
    for(int i = 0; i < MAX_SIZE_TABLA; i++) tabla->elementos[i] = NULL;

    tabla->tipo = tipo;

    if(tipo == T_Funciones){

    tabla_agregar_funcion(tabla,"0i",F_PRIMITIVA,Oi);
    tabla_agregar_funcion(tabla,"0d",F_PRIMITIVA,Od);
    tabla_agregar_funcion(tabla,"Di",F_PRIMITIVA,Di);
    tabla_agregar_funcion(tabla,"Dd",F_PRIMITIVA,Dd);
    tabla_agregar_funcion(tabla,"Si",F_PRIMITIVA,Si);
    tabla_agregar_funcion(tabla,"Sd",F_PRIMITIVA,Sd);
    tabla_agregar_funcion(tabla,"<",F_BANDERA,NULL);
    tabla_agregar_funcion(tabla,">",F_BANDERA,NULL);

    }

    return tabla;
}

