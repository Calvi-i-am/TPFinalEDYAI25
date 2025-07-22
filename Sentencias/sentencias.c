#include "sentencias.h"

void defl(char * cadena, Tabla tabla){

    if (tabla->tipo != T_Listas) return; //Comprobamos tipo de tabla

    Lista list = lista_crear();

    
    //Copio la cadena para usarla en search
    char * inicio_cadena = cadena;
    while(*inicio_cadena != '=') inicio_cadena++;
    inicio_cadena++; inicio_cadena++;
    strcpy(list->EnCadena,inicio_cadena);

    //Resultado temporal = [nums1,nums2,..]; , eliminemos ese ";"

    char * punto_y_coma = strchr(list->EnCadena,';');
    *punto_y_coma = '\0';

    //Asi tenemos que: list->EnCadena [nums1,nums2,..]


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
    for(int i = 0; token != NULL && i < MAX_COMPOSICION && BienLeido;){
        if(token[0] == '<' || token[0] == '>'){//Comienza repeticion, agrego la bandera
            char * temp = malloc(sizeof(char) * 2); temp[0] = token[0]; temp[1] = '\0';
            f->subfunciones[i] = tabla_buscar_f(temp,tabla);
            free(temp);
            token++;
            i++;
        }
        Funcion actual = tabla_buscar_f(token,tabla);
        if(actual != NULL){//Existe esta funcion en la tabla
            f->subfunciones[i] = actual;
            token = strtok(NULL, " ,;");
            i++;
        }
        else{
            printf("La subfuncion %s no fue previamente definida "
            "en la definicion de %s\n", token, f->nombre);
            BienLeido = 0;
        }
    }

    free(cadena);

    if (!BienLeido){
        free(f);
        return;
    }
    tabla_agregar_funcion(tabla, f->nombre, F_COMPUESTA, f);


}