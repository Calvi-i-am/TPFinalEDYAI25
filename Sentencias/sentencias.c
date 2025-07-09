#include "sentencias.h"

void defl(char * cadena, Tabla * tabla){

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

void deff(char * cadena, Tabla * tabla){

    if (tabla->tipo != T_Funciones) return; //Comprobamos tipo de tabla


    Funcion * f = malloc(sizeof(Funcion));

    char * token = strtok(cadena, " ");
    strcpy(f->nombre,token);

    token = strtok(NULL, " ,;");

    //Este token equivale al nombre de la primera funcion:
    //Si contiene un '<' en el primer caracter, entonces la
    //funcion es de tipo repeticion, esta f se va a cerrar
    //cuando se encuente un caracter con '>'.
    //Si luego de ese caracter se encuentra otra funcion en la cadena
    //Entonces, la funcion principal es una nueva, la cual sera 
    //una funcion compuesta entre la f recursiva ya creada
    //con el resto

    //Si no tiene un '<' al comienzo, es entonces una funcion compuesta
    //(Aunque tenga uno despues, podemos decir que es una compuesta con
    //alguna repeticion de por medio)

    for(int i = 0; token != NULL && i <= MAX_COMPOSICION; i++){
        Funcion * actual = tabla_buscar_f(token,tabla);
        if(actual != NULL){
            f->subfunciones[i] = actual;
        }
    }


}