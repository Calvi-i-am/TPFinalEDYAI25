#include "Sentencias/sentencias.h"


Lista apply_compuestas(Lista list, Funcion f, Tabla tablaFunc,int inicio, int final){
    for(int i = inicio; i < final; i++){
        Funcion subf = f->subfunciones[i];
        if (subf->Tipo == F_PRIMITIVA){
            list = subf->primitiva(list);
        }
        else if (subf->Tipo == F_COMPUESTA){
            list = apply_compuestas(list, subf, tablaFunc, 0, subf->cantidad_subfunciones);
        }
        else{ 
            int inicio_repe = ++i;
            int final_repe = inicio_repe;
            for(; strcmp(f->subfunciones[inicio_repe]->nombre,">") || inicio_repe < final; final_repe++)
            
            while(list->primero != list->ultimo){
                printf("Se ejecuta la repeticion de la funcion %s\n", f->subfunciones[inicio_repe]->nombre);
            list = apply_compuestas(list, f, tablaFunc, inicio_repe, final_repe);}
        }
    }
    return list;

}



Lista apply_listas(Lista list, Funcion f, Tabla tablaFunc){
    if (f->Tipo == F_PRIMITIVA) return f->primitiva(list);
    return apply_compuestas(list, f, tablaFunc, 0, f->cantidad_subfunciones);
}



