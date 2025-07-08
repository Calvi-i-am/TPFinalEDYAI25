#include "tablas.h"



unsigned KRHashN(char *s, int n) {
  unsigned hashval;
  for (hashval = 0; *s != '\0'; ++s) {
    hashval = *s + 31 * hashval;
  }
  return hashval % n;
}



int tabla_full(Tabla * tabla){
    return (tabla->cantidad >= MAX_SIZE_TABLA);
}

void tabla_agregar_lista(Tabla * tabla, Lista list){

    if(tabla->tipo != T_Listas) return;

    int idx = tabla->FHash(list->nombre,tabla->cantidad);
    for(int i = 1; tabla->elementos[idx] != NULL && !(tabla_full(tabla)); i++)
        idx = (idx + 1) % MAX_SIZE_TABLA;

    tabla->elementos[idx] = list;

}

void tabla_agregar_primitiva(Tabla * tabla, char * nombre,
FuncionLista f){

    if(tabla->tipo != T_Funciones) return;


    Funcion * PRIMITIVA = malloc(sizeof(Funcion));
    strcpy(PRIMITIVA->nombre,nombre);
    PRIMITIVA->Tipo = F_PRIMITIVA;
    PRIMITIVA->primitiva = f;

    int idx = KRHashN(nombre, MAX_SIZE_TABLA);
    for(int i = 1; tabla->elementos[idx] != NULL && !(tabla_full(tabla)); i++)
        idx = (idx + 1) % MAX_SIZE_TABLA; //linear probing simple

    tabla->elementos[idx] = PRIMITIVA;
    
    tabla->cantidad++;
    
     }

Tabla * tabla_crear(){
    Tabla * tabla = malloc(sizeof(Tabla));
    tabla->cantidad = 0;
    tabla->FHash = KRHashN;
    for(int i = 0; i < MAX_SIZE_TABLA; i++) tabla->elementos[i] = NULL;

    tabla_agregar_primitiva(tabla,"0i",Oi);
    tabla_agregar_primitiva(tabla,"0d",Od);
    tabla_agregar_primitiva(tabla,"Si",Si);
    tabla_agregar_primitiva(tabla,"Sd",Sd);
    tabla_agregar_primitiva(tabla,"Di",Di);
    tabla_agregar_primitiva(tabla,"Dd",Dd);

    return tabla;
}

Tabla * tabla_crear(Tipo_Tabla tipo){
    Tabla * tabla = malloc(sizeof(Tabla));
    tabla->cantidad = 0;
    tabla->FHash = KRHashN;

    tabla->tipo = tipo;

    return tabla;
}





int main() {
    Tabla *tabla = tabla_crear();  // crea y carga las primitivas

    printf("Contenido de la tabla hash:\n");
    printf("--------------------------------\n");

    for (int i = 0; i < MAX_SIZE_TABLA; i++) {
        printf("Índice %3d: ", i);
        if (tabla->elementos[i] != NULL) {
            Funcion *f = tabla->elementos[i];
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