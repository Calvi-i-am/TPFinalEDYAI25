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
        printf("Token: %s\n", token); //Debug
        int numero = atoi(token);
        lista_add_nodo(list,numero);
        token = strtok(NULL, " ,[];"); //strtok tiene memoria de que cadena
                                      //estaba leyendo, por eso NULL, si
                                      //pasamos cadena de nuevo, se reinicia.
    }
    free(cadena);

    printf("Lista %s creada con exito\n", list->nombre);

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

        if(token[0] == '<'){//Comienza repeticion, agrego la bandera
            char * temp = malloc(sizeof(char) * 2); temp[0] = token[0]; temp[1] = '\0';
            f->subfunciones[i] = (Funcion) tabla_buscar(tabla,temp);
            free(temp);
            f->cantidad_subfunciones++;
            token++;
            i++;
        }

        int len = strlen(token);


        if(token[len-1] == '>'){//Termina repeticion, agrego la bandera
            char * temp = malloc(sizeof(char) * 2); temp[0] = token[len-1]; temp[1] = '\0';
            f->subfunciones[i+1] = (Funcion) tabla_buscar(tabla,temp);
            free(temp);
            f->cantidad_subfunciones++;
            token[len-1] = '\0'; //Elimino el caracter de cierre
        }

        Funcion actual = (Funcion) tabla_buscar(tabla,token);
        if(actual != NULL){//Existe esta funcion en la tabla
            if(f->subfunciones[i] == NULL){
            f->subfunciones[i] = actual;
            token = strtok(NULL, " ,;");
            f->cantidad_subfunciones++;
            }
        }
        else{
            printf("La subfuncion %s no fue previamente definida "
            "que la defincion de %s\n", token, f->nombre);
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
        printf("Parado en el indice: %d\n", i);
        Funcion subf = f->subfunciones[i];
        if (subf->Tipo == F_PRIMITIVA){
                printf("funcion a ejecutar: %s\n", f->subfunciones[i]->nombre);

            list = subf->primitiva(list);
        }
        else if (subf->Tipo == F_COMPUESTA){
            printf("funcion a ejecutar: %s\n", f->subfunciones[i]->nombre);

            list = apply_compuestas(list, subf, tablaFunc, 0, subf->cantidad_subfunciones);
        }


        else if (subf->Tipo == F_BANDERA){ //Es una bandera, se ejecuta repeticion
            int cont_banderas = 1;
            int inicio_repe = i + 1;
            int final_repe = inicio_repe;
            
            while (cont_banderas > 0 && final_repe < final){
                final_repe++;
                if (strcmp(f->subfunciones[final_repe]->nombre,">") == 0){
                    cont_banderas--;
                }
                else if (strcmp(f->subfunciones[final_repe]->nombre,"<") == 0){
                    cont_banderas++;
                }
            
            }
            

            while(list->primero->dato != list->ultimo->dato){
                list = apply_compuestas(list, f, tablaFunc, inicio_repe, final_repe);

                
            }

            i  = final_repe; //Ajusto i para saltar las banderas

        }
    
        if(strcmp(f->nombre, "S") == 0){
        printf("Lista luego de aplicar %s: ", subf->nombre);
        SNodo * actual = list->primero;
        while (actual != NULL) {
            printf("%d ", actual->dato);
            actual = actual->sig;
    } printf("\n");
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


    free(cadena);
    
    //Con la funcion y la lista ya encontradas,
    //procedemos a aplicar la funcion.

    printf("Aplicando funcion %s a lista %s\n", f->nombre, list->nombre);

    return apply_listas(list, f, tablaFunc);


}

int main() {
    // Crear tablas
    Tabla tablaF = tabla_crear(T_Funciones);
    Tabla tablaL = tabla_crear(T_Listas);

    // Definir una lista: defl
    char *entrada_lista = strdup("listaA = [];");
    defl(entrada_lista, tablaL);

    // Definir otra lista
    char *entrada_lista2 = strdup("listaB = [0,1,2];");
    defl(entrada_lista2, tablaL);

    // Definir una función compuesta: deff
    // Por ejemplo: "sumar Si Di" (aplica Si y luego Di)
    char *entrada_funcion = strdup("Mi Oi <Si> Dd");
    deff(entrada_funcion, tablaF);

    // Definir una función compuesta: deff
    // Por ejemplo: "sumar Si Di" (aplica Si y luego Di)
    entrada_funcion = strdup("Md Od <Sd> Di");
    deff(entrada_funcion, tablaF);

    // Definir una función compuesta: deff
    // Por ejemplo: "sumar Si Di" (aplica Si y luego Di)
    entrada_funcion = strdup("DDi Od <Sd> Mi");
    deff(entrada_funcion, tablaF);

        // Definir una función compuesta: deff
    // Por ejemplo: "sumar Si Di" (aplica Si y luego Di)
    entrada_funcion = strdup("S DDi Si Md Di DDi Si Md Di DDi Si Md Di");
    deff(entrada_funcion, tablaF);



    // Aplicar función a lista: apply
    char *entrada_apply = strdup("S listaB");
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
