//Cabrera Alvaro, 2025.
//--------------------------

//Implementacion de funciones auxiliares y del parser

//--------------------------

#include "parser.h"

char * copiar_subcadena(char ** str){
    char * subcadena = malloc(sizeof(char) * 150);
    int j = 0; //casillas avanzadas
    for(; (*str)[j] != ';' && (*str)[j] != '\0' && j<150 ; j++) 
        //hasta q vea ; , \0 o se llene subcadena
        subcadena[j] = (*str)[j];

    subcadena[j] = '\0';
    (*str) += j + 1;

    return subcadena;
}

void parser(char * str){
    while(*str != '\0'){ //final de cadena
        // Saltar espacios
        while (*str == ' ') str++;

        char  funcion[10]; int i = 0;

        for(; i<10 && str[i] != ' '; i++){
            funcion[i] = str[i]; 
        }
        funcion[i] = '\0';
        printf("funcion leida: %s", funcion);

        //Porque use esto y no strtok? Justificacion 1.

        if(strcmp(funcion,"deff") == 0){
            char * subcadena = copiar_subcadena(&str);
            printf("Procesando deff: '%s'\n", subcadena);
            //deff(subcadena)
        }
        else if(strcmp(funcion,"defl") == 0){
            char * subcadena = copiar_subcadena(&str);
            printf("Procesando defl: '%s'\n", subcadena);
            //defl(subcadena)
        }
        else if(strcmp(funcion, "apply") == 0){
            char * subcadena = copiar_subcadena(&str);
            printf("Procesando apply: '%s'\n", subcadena);
            //apply(subcadena)
        }
        else if(strcmp(funcion,"search") == 0){
            char * subcadena = copiar_subcadena(&str);
            printf("Procesando search: '%s'\n", subcadena);
            //defl(subcadena)
        }
        else
        {
            printf("comando desconocido");
            while(*str != '\0') str++;
             //para terminar el parseo, la funcion siguiente
            // es irreconocible
        }
        
        
    }
    
    printf("yupiiiiii");
}



int main() {
    char entrada[] = "deff f = s0 si d0; defl g = [0,2,4,6]; otro comando; \0";

    printf("Cadena a parsear:\n%s\n\n", entrada);

    parser(entrada);

    return 0;
}