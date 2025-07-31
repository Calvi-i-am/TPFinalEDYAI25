//Cabrera Alvaro, 2025
//--------------------------

#include "sentencias.h"

void defl(char * cadena, Tabla tabla){

    if (tabla->tipo != T_Listas) return; //Comprobamos tipo de tabla

    Lista list = lista_crear();


    //Guardo el nombre de la lista
    char * token = strtok(cadena," ,[]");

    if (tabla_buscar(tabla, token) != NULL){ //Si la lista ya existe, no la agrego
        printf("La lista %s ya fue previamente definida.\n", token);
        return;
    }

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
    

    printf("Lista %s creada con exito\n", list->nombre);

    tabla_agregar_lista(tabla,list);
}

void deff(char * cadena, Tabla tabla){

    if (tabla->tipo != T_Funciones) return; //Comprobamos tipo de tabla

    char * token = strtok(cadena, " ");

    if(tabla_buscar(tabla, token) != NULL){//Si la funcion ya existe, no la agrego
        printf("La funcion %s ya fue previamente definida.\n", token);
        return;
    }



    Funcion f = malloc(sizeof(_Funcion));
    f->Tipo = F_COMPUESTA;
    f->cantidad_subfunciones = 0; //Inicializo cantidad de subfunciones a 0
    for(int i = 0; i < MAX_COMPOSICION; i++)
    f->subfunciones[i] = NULL; //Inicializo subfunciones a NULL
    strcpy(f->nombre,token);


    token = strtok(NULL, " ,;=");
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


    if (!BienLeido){//En caso de error, no agrego la funcion a la tabla
        free(f);
        return;
    }
    tabla_agregar_funcion(tabla, f->nombre, F_COMPUESTA, f);



}

Lista string_a_lista(char * cadena, Tabla tablaLists){

    if (cadena == NULL) return NULL;

    if (cadena[0] == '['){//Lista en formato explicita
        Lista list = lista_crear();
        while(cadena != NULL){
            int numero = atoi(cadena);
            lista_add_nodo(list,numero);
            cadena = strtok(NULL, " ,[];");
        }
        return list;
        
    }
    else{//Lista en formato nombre
        Lista list = (Lista) tabla_buscar(tablaLists, cadena); 
        if (list == NULL){
            printf("No se encontro la lista a aplicar: %s\n", cadena);
            free(list);
            return NULL;
        }
        return list;
    }
}

Lista apply_compuestas(Lista list, Funcion f, Tabla tablaFunc,int inicio, int final){
    for(int i = inicio; i < final; i++){
        Funcion subf = f->subfunciones[i]; 
        if (subf->Tipo == F_PRIMITIVA){
            list = subf->primitiva(list); 
        }
        else if (subf->Tipo == F_COMPUESTA){
            //Si es compuesta, aplico apply_compuestas recursivamente
            list = apply_compuestas(list, subf, tablaFunc, 0, subf->cantidad_subfunciones); 
        }

        else if (subf->Tipo == F_BANDERA){ //Es una bandera de repeticion
            //Vamos a tomar desde despues de la bandera hasta que
            //encontremos la bandera de cierre, y aplicamos apply_compuestas

            int cont_banderas = 1;
            int inicio_repe = i + 1; //Primer subfuncion en la repeticion
            int final_repe = inicio_repe; //Actual final de la repeticion

            //Mientras la cantidad de "<" y ">" no sean iguales,
            //es porque hay una repeticion abierta

            while (cont_banderas > 0 && final_repe < final){
                final_repe++;
                if(f->subfunciones[final_repe]->Tipo == F_BANDERA){
                    if (strcmp(f->subfunciones[final_repe]->nombre,">") == 0){
                        cont_banderas--;
                    }
                    else if (strcmp(f->subfunciones[final_repe]->nombre,"<") == 0){
                        cont_banderas++;
                    }
                }
            }
            //Ejecutamos apply_compuestas en el rango de inicio_repe a final_repe
            //siempre y cuando el primero de la lista sea distinto al ultimo,
            //aprovechando los indices de inicio y final que toma apply_compuestas
            if(list && list->primero && list->ultimo){
                int pasadas = 0; //Contador de pasadas
                while(list->primero->dato != list->ultimo->dato){
                    list = apply_compuestas(list, f, tablaFunc, inicio_repe, final_repe);
                    pasadas++;
                    if (pasadas == 1000) //Bandera de aviso
                        printf("Demasiadas pasadas en la repeticion, posible bucle infinito.\n");
                }
            }

            i  = final_repe; //Ajusto i para saltar la repeticion ya evaluada
        }
}
    return list;
}



Lista apply_listas(Lista list, Funcion f, Tabla tablaFunc){
    if (f->Tipo == F_PRIMITIVA) return f->primitiva(list);
    return apply_compuestas(list, f, tablaFunc, 0, f->cantidad_subfunciones);
}





void apply(char * cadena, Tabla tablaFunc, Tabla tablaLists){
    if (tablaFunc->tipo != T_Funciones || tablaLists->tipo != T_Listas) return;

    char * token = strtok(cadena, " =,"); //Este es el nombre de la funcion a aplicar
    Funcion f = (Funcion) tabla_buscar(tablaFunc, token);
    if (f == NULL){
        printf("No se encontro la funcion a aplicar: %s\n", token);
        return;
    }

    token = strtok(NULL, " =,"); //Esta es el primer elem de la lista en exten.
                                  // o el nombre de la lista
    if (token == NULL){
        printf("La lista %s no fue ingresada correctamente\n", token);
        return;
    }



    Lista list = string_a_lista(token, tablaLists);
    if (list == NULL){
        printf("No se pudo crear la lista a partir de la entrada: %s\n", token);
        return;
    }

    Lista resultado = lista_copiar(list); //Copio la lista para no modificar la original
    if (resultado == NULL){
        printf("No se pudo crear una copia de la lista %s\n", list->nombre);
        free(list);
        return;
    }

    
    //Con la funcion y la lista ya encontradas,
    //procedemos a aplicar la funcion.

    printf("Aplicando funcion %s a lista %s\n", f->nombre, resultado->nombre);

    apply_listas(resultado, f, tablaFunc);
    lista_imprimir(resultado);
    lista_eliminar(resultado); //Libero la lista resultante
    
    

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

int search(char * cadena, Tabla tablaFunc, Tabla tablaList){
    if (tablaFunc->tipo != T_Funciones || tablaList->tipo != T_Listas) return 0;

    int k = tablaFunc->cantidad; //K indica la cantidad de ramificaciones que tiene el arbol

    Lista * listas = malloc(sizeof(Lista) * 100); //Suponemos menos de 50 pares
    char * token = strtok(cadena, " ,[];");
    for(int i = 0; i < 100 && strcmp(token,"}") == 0; i++) {
        listas[i] = string_a_lista(cadena, tablaList);
    }

    Funcion * funciones = malloc(sizeof(Funcion) * k);
    int j = 0;
    for(int i = 0; i < k; i++){
        Funcion f = (Funcion) tablaFunc->elementos[i];
        if (f != NULL && f->Tipo == F_BANDERA){
            funciones[j] = f;
            j++;
        }
    }

    int ListasVisitadas[10000]; //Arreglo con los indices de las listas visitadas
    Lista tree[10000]; //Arreglo con las listas visitadas
    Lista cola[10000]; //Cola para crear el arbol de busqueda
    int top = 0; //Indice del tope de la cola

    int cont = 0; //Indice del arbol;

    cola[top] = listas[0]; //Agrego la primera lista a la cola
    ListasVisitadas[ListHashN(listas[0],10000)] = 1; //Marcamos la primera lista como visitada
}