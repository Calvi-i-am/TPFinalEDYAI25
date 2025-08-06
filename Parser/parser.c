//Cabrera Alvaro, 2025.
//--------------------------

//Implementacion de funciones auxiliares y del parser

//--------------------------

#include "parser.h"

char * copiar_subcadena(char ** str, char * Funcion){
    char * subcadena = malloc(sizeof(char) * 150);
    char corte = (strcmp(Funcion, "search") != 0) ? ';' : '}'; //Si es search, el corte es }, sino es ;

    int j = 0; //casillas avanzadas
    for(; (*str)[j] != corte && (*str)[j] != '\0' && j<150 ; j++) 
        //hasta q vea ; , \0 o se llene subcadena
        subcadena[j] = (*str)[j];

    if (strcmp(Funcion, "search") == 0) subcadena[j++] = '}'; //Si es search, agrego el cierre
    subcadena[j] = '\0';
    (*str) += j + 1;

    return subcadena;
}

void parser(char * str, Tabla tablaFunc, Tabla tablaLists){
    printf("Cadena a parsear: %s\n", str); //Debug

    while(*str != '\0'){ //final de cadena
        while(*str == ' ') str++; //Saco espacios al principio

        char funcion[10] ; int i = 0;

        for(; i<10 && str[i] != ' '; i++){
            funcion[i] = str[i]; 
        }
        funcion[i] = '\0';
        str += i + 1; //Le saco lo copiado a la cadena


        char * subcadena = copiar_subcadena(&str, funcion);
        printf("Funcion: '%s', Subcadena: '%s'\n", funcion, subcadena); //Debug

        if(strcmp(funcion,"deff") == 0){
            printf("Procesando deff: '%s'\n", subcadena);
            deff(subcadena, tablaFunc);
        }
        else if(strcmp(funcion,"defl") == 0){
            printf("Procesando defl: '%s'\n", subcadena);
            defl(subcadena, tablaLists);
        }
        else if(strcmp(funcion, "apply") == 0){
            printf("Procesando apply: '%s'\n", subcadena);
            apply(subcadena, tablaFunc, tablaLists);
        }
        else if(strcmp(funcion,"search") == 0){
            printf("Procesando search: '%s'\n", subcadena);
            search(subcadena, tablaFunc, tablaLists);
        }
        else if(strcmp(funcion,"tablas") == 0){
            printf("Procesando tablas:\n");
            for(int i = 0, j = 0; i < tablaFunc->cantidad && j < MAX_SIZE_TABLA; j++){
                Funcion funcion = tablaFunc->elementos[j];
                if (funcion != NULL && strcmp(funcion->nombre, ">") != 0 && strcmp(funcion->nombre, "<") != 0){
                    printf("Funcion numero %d: %s\n", i , funcion->nombre);
                    i++;
                }
            }
            printf("Procesando listas:\n");
            for(int i = 0, j = 0; i < tablaLists->cantidad && j < MAX_SIZE_TABLA; j++){
                Lista funcion = tablaLists->elementos[j];
                if (funcion != NULL && strcmp(funcion->nombre, ">") != 0 && strcmp(funcion->nombre, "<") != 0){
                    printf("Funcion numero %d: %s\n", i , funcion->nombre);
                    i++;
                }
            }
        }
        else
        {
            printf("comando desconocido");
            while(*str != '\0') str++;
             //para terminar el parseo, la funcion siguiente
            // es irreconocible
        }
        free(subcadena); //Libero memoria de la subcadena copiada
    }
}
