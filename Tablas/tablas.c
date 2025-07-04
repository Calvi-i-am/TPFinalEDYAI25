#include "tablas.h"
#include "../Funciones/Funciones.h"

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