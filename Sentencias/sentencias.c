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
    f->Tipo = f_compuesta;
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
    tabla_agregar_funcion(tabla, f->nombre, f_compuesta, f);



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
            return NULL;
        }
        return list;
    }
}

Lista apply_compuestas(Lista list, Funcion f, Tabla tablaFunc,int inicio, int final){
    for(int i = inicio; i < final; i++){
        Funcion subf = f->subfunciones[i]; 
        if (subf->Tipo == f_primitiva){
            list = subf->primitiva(list); 
        }
        else if (subf->Tipo == f_compuesta){
            //Si es compuesta, aplico apply_compuestas recursivamente
            list = apply_compuestas(list, subf, tablaFunc, 0, subf->cantidad_subfunciones); 
        }

        else if (subf->Tipo == f_bandera){ //Es una bandera de repeticion
            //Vamos a tomar desde despues de la bandera hasta que
            //encontremos la bandera de cierre, y aplicamos apply_compuestas

            int cont_banderas = 1;
            int inicio_repe = i + 1; //Primer subfuncion en la repeticion
            int final_repe = inicio_repe; //Actual final de la repeticion

            //Mientras la cantidad de "<" y ">" no sean iguales,
            //es porque hay una repeticion abierta

            while (cont_banderas > 0 && final_repe < final){
                final_repe++;
                if(f->subfunciones[final_repe]->Tipo == f_bandera){
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
    if (f == NULL) return NULL;
    if (f->Tipo == f_primitiva) return f->primitiva(list);
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



int tabla_buscar_lista(Lista * ListasVisitadas, Lista list, int idx){
    int cont = 0;
    int encontrado = 0;
    while(ListasVisitadas[idx] != NULL && !(encontrado) && cont < MAX_SIZE_BFS){
        if (lista_comparar(list, ListasVisitadas[idx]) == 1)
            encontrado = 1;
        else {
            idx = (idx + 1) % MAX_SIZE_TABLA; //linear probing simple
        }
        cont++;
    }
    return encontrado;
}


void search(char * cadena, Tabla tablaFunc, Tabla tablaList){
    if (tablaFunc->tipo != T_Funciones || tablaList->tipo != T_Listas) return;

    
    int cant_listas = 10;
    Lista * listas = calloc(cant_listas ,sizeof(Lista));
    char * token = strtok(cadena, " ;]");
    if (strcmp(token,"{") != 0) return;
    int i = 0;
    token = strtok(NULL,";, ");
    printf("token %s\n", token);
    while (token != NULL && strcmp(token, "}") != 0) {
        listas[i++] = string_a_lista(token, tablaList);
        if (i >= cant_listas - 1) {
            cant_listas *= 2;
            listas = realloc(listas, sizeof(Lista) * cant_listas);
        }

        token = strtok(NULL, ";, ");
    }
    listas[i] = NULL;
    

    for(int i = 0; listas[i] != NULL; i++) {lista_imprimir(listas[i]);
    printf("\n");
    }

    
    

    Funcion * funciones = malloc(sizeof(Funcion) * tablaFunc->cantidad - 2); 
    //Restamos 2 por ">" "<" que estan la tabla pero no son funciones
    int j = 0;
    for(int i = 0; j < tablaFunc->cantidad-2 && i < MAX_SIZE_TABLA; i++){
        Funcion f = (Funcion) tablaFunc->elementos[i];
        if (f != NULL && f->Tipo != f_bandera){
            funciones[j] = f;
            j++;
        }
    }
    funciones[j] = NULL; //Ultimo elemento NULL para determinar el final


    Lista * ListasVisitadas = malloc(sizeof(Lista) * MAX_SIZE_BFS);
    for(int i = 0; i < MAX_SIZE_BFS; i++){
        ListasVisitadas[i] = NULL; //Inicializo las listas visitadas a NULL
    }
    int ListasVisitadasCont = 0;
    NodoBFS arbol[MAX_SIZE_BFS];

    arbol[0].lista = listas[0];
    arbol[0].funcion = NULL;
    arbol[0].padre_idx = -1; //El nodo raiz no tiene padre
    arbol[0].nivel = 0; 

    int padre = 0;
    int cont = 1; //Contador de nodos en el arbol
    int Resultado = 0; //Bandera de si se encontro un resultado
    

    while(cont < MAX_SIZE_BFS && !(Resultado)){
        if (arbol[padre].lista != NULL){ // Si el padre tiene lista vacia, no es valido
                for(int j = 0; j < tablaFunc->cantidad - 2 && cont < MAX_SIZE_BFS; j++){

                Funcion f = funciones[j];
                Lista list_copia = lista_copiar(arbol[padre].lista); 
                list_copia = apply_listas(list_copia, f, tablaFunc);

                int idx = ListHashN(list_copia, MAX_SIZE_BFS); //Calcula el hash de la lista resultante

                if(tabla_buscar_lista(ListasVisitadas, list_copia, idx) == 0){ //En caso que no la encontre
                    arbol[cont].funcion = f; 
                    arbol[cont].lista = list_copia;
                    arbol[cont].padre_idx = padre;
                    arbol[cont].nivel = arbol[padre].nivel + 1;

                    for(int k = 0; k < MAX_SIZE_BFS && ListasVisitadas[idx] != NULL; k++){
                        idx = (idx + 1) % MAX_SIZE_BFS; //Busco un espacio libre
                    }
                    ListasVisitadas[idx] = arbol[cont].lista;
                    ListasVisitadasCont++;
            
                    //Veamos si es la secuencia que buscamos
                    if (lista_comparar(arbol[cont].lista, listas[1]) == 1){
                        lista_imprimir(listas[1]);
                        lista_imprimir(arbol[cont].lista);
                        printf("Se encontro una secuencia de funciones que resuelve el primer par\n");
                        Funcion posible = malloc(sizeof(_Funcion));
                        strcpy(posible->nombre, "");
                        posible->Tipo = f_compuesta;
                        posible->cantidad_subfunciones = 0;

                        for(int i = 0; i < MAX_COMPOSICION; i++) posible->subfunciones[i] = NULL;
                        int actual = cont; //Empezamos desde el nodo actual

                        

                        //Buscamos agregar el padre siempre y cuando el nivel actual sea > 0

                        for(int nivel = arbol[cont].nivel; nivel > 0 && actual > 0; nivel--){ //A
                            posible->subfunciones[nivel - 1] = arbol[actual].funcion;
                            posible->cantidad_subfunciones++;
                            actual = arbol[actual].padre_idx; //Vamos al padre
                        }
                        //Con la funcion ya creada, la probamos

                        int es_valida = 1;

                        for (int i = 2; listas[i] && listas[i+1] && es_valida; i += 2){
                            Lista copia1 = lista_copiar(listas[i]);
                            Lista copia2 = lista_copiar(listas[i+1]);
                            copia1 = apply_listas(copia1, posible, tablaFunc);
                            copia2 = apply_listas(copia2, posible, tablaFunc);
                            if (lista_comparar(copia1, copia2) != 1) es_valida = 0;
                            lista_eliminar(copia1); lista_eliminar(copia2);
                        }
                        if (es_valida){
                            printf("Se encontro una secuencia de funciones que resuelve el problema:\n");
                            for(int i = 0; i < posible->cantidad_subfunciones ; i++){
                                printf("%s ", posible->subfunciones[i]->nombre);
                            }
                            printf("pos: %d", cont);
                            Resultado = 1; //Indicamos que se encontro un resultado
                        }  
                        else{
                            printf("La secuencia de funciones no resuelve el problema.\n");
                            free(posible); //Liberamos la memoria de la funcion
                        }
                    }
                }
                else{
                    arbol[cont].lista = NULL; //Esta casilla no es un padre valido
                    lista_eliminar(list_copia);
                }
            cont++;
        
            }
        }
        padre++;
    }

    if(!Resultado) printf("No se consiguio una secuencia valida\n");


    //Liberamos la memoria
    for(int i = 0; i < cant_listas; i++){
        lista_eliminar(listas[i]);
    }
    free(listas);
    for(int i = 0 ; i < MAX_SIZE_BFS ; i++){
        if (ListasVisitadas[i] != NULL) 
        lista_eliminar(ListasVisitadas[i]);
    }
    free(ListasVisitadas);
    free(funciones);
}