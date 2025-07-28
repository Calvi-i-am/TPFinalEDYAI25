#include "sentencias.h"

void defl(char * cadena, Tabla tabla){

    if (tabla->tipo != T_Listas) return; //Comprobamos tipo de tabla

    Lista list = lista_crear();


    //Guardo el nombre de la lista
    char * token = strtok(cadena," ,[]");
    strcpy(list->nombre,token);



    //Voy tomando cada numero, lo paso a su int equivalente
    //y creo un nodo con ese numero para anadirlo a la lista
    token = strtok(NULL, " ,[]=;");
    while(token != NULL){
        int numero = atoi(token);
        lista_add_nodo(list,numero);
        token = strtok(NULL, " ,[];"); //strtok tiene memoria de que cadena
                                      //estaba leyendo, por eso NULL, si
                                      //pasamos cadena de nuevo, se reinicia.
    }
    free(cadena);

    tabla_agregar_lista(tabla,list);
}

void deff(char * cadena, Tabla tabla){

    if (tabla->tipo != T_Funciones) return; //Comprobamos tipo de tabla


    Funcion f = malloc(sizeof(_Funcion));
    f->Tipo = F_COMPUESTA;
    for(int i = 0; i < MAX_COMPOSICION; i++)
     f->subfunciones[i] = NULL; //Inicializo subfunciones a NULL
    char * token = strtok(cadena, " ");
    strcpy(f->nombre,token);


    token = strtok(NULL, " ,;");
    int BienLeido = 1; //Booleano que determina si no hubo errores en la lectura
    //Se usara principalmente por si alguna funcion ingresada no fue previamente
    //definida.
    for(int i = 0; token != NULL && i < MAX_COMPOSICION && BienLeido;i++){
        if(token[0] == '<' || token[0] == '>'){//Comienza repeticion, agrego la bandera
            char * temp = malloc(sizeof(char) * 2); temp[0] = token[0]; temp[1] = '\0';
            f->subfunciones[i] = (Funcion) tabla_buscar(tabla,temp);
            free(temp);
            f->cantidad_subfunciones++;
            token++;
        }
        Funcion actual = (Funcion) tabla_buscar(tabla,token);
        if(actual != NULL){//Existe esta funcion en la tabla
            f->subfunciones[i] = actual;
            token = strtok(NULL, " ,;");
            f->cantidad_subfunciones++;
        }
        else{
            printf("La subfuncion %s no fue previamente definida "
            "en la definicion de %s\n", token, f->nombre);
            BienLeido = 0;
        }
    }

    free(cadena);

    if (!BienLeido){//En caso de error, no agrego la funcion a la tabla
        free(f);
        return;
    }
    tabla_agregar_funcion(tabla, f->nombre, F_COMPUESTA, f);



}

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
            
            while(list->primero != list->ultimo) 
            list = apply_compuestas(list, f, tablaFunc, inicio_repe, final_repe);
        }
    }
    return list;

}



Lista apply_listas(Lista list, Funcion f, Tabla tablaFunc){
    if (f->Tipo == F_PRIMITIVA) return f->primitiva(list);
    return apply_compuestas(list, f, tablaFunc, 0, f->cantidad_subfunciones);
}




Lista apply(char * cadena, Tabla tablaFunc, Tabla tablaLists){
    if (tablaFunc->tipo != T_Funciones || tablaLists->tipo != T_Listas) return NULL;

    char * token = strtok(cadena, " =,"); //Este es el nombre de la funcion a aplicar
    Funcion f = (Funcion) tabla_buscar(tablaFunc, token);
    if (f == NULL){
        printf("No se encontro la funcion a aplicar: %s\n", token);
        return NULL;
    }

    token = strtok(NULL, " =,"); //Esta es el primer elem de la lista en exten.
                                  // o el nombre de la lista
    if (token == NULL){
        printf("La funcion %s no fue previamente ingresada\n", token);
        return NULL;
    }


    Lista list = lista_crear();

    if (token[0] == '['){
        while(token != NULL){
            int numero = atoi(token);
            lista_add_nodo(list,numero);
            token = strtok(NULL, " ,[];");
        }
        
    }
    else{
        list = (Lista) tabla_buscar(tablaLists, token);
        if (list == NULL){
            printf("No se encontro la lista a aplicar: %s\n", token);
            free(list);
            return NULL;
        }
    }

    free(token);
    free(cadena);
    
    //Con la funcion y la lista ya encontradas,
    //procedemos a aplicar la funcion.

    return apply_listas(list, f, tablaFunc);


}

int main() {
    // Crear tablas
    Tabla tablaF = tabla_crear(T_Funciones);
    Tabla tablaL = tabla_crear(T_Listas);

    // Definir una lista: defl
    char *entrada_lista = strdup("listaA = [1,2,3,4,5];");
    defl(entrada_lista, tablaL);

    // Definir otra lista
    char *entrada_lista2 = strdup("listaB = [10,20,30];");
    defl(entrada_lista2, tablaL);

    // Definir una función compuesta: deff
    // Por ejemplo: "sumar Si Di" (aplica Si y luego Di)
    char *entrada_funcion = strdup("sumar Si Di");
    deff(entrada_funcion, tablaF);

    // Aplicar función a lista: apply
    char *entrada_apply = strdup("sumar = listaA");
    Lista resultado = apply(entrada_apply, tablaF, tablaL);

    // Mostrar resultado
    printf("Resultado de aplicar 'sumar' a 'listaA': [");
    SNodo *actual = resultado->primero;
    while (actual != NULL) {
        printf("%d", actual->dato);
        if (actual->sig != NULL) printf(", ");
        actual = actual->sig;
    }
    printf("]\n");

    // Liberar memoria si corresponde (no implementado aquí)
    return 0;
}
