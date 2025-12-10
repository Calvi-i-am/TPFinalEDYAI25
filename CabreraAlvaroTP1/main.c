#include <stdio.h>
#include <stdlib.h>
#define _POSIX_C_SOURCE 200809L
#include <string.h>
#include "Parser/Parser.h"

int main(){
    
    //Inicializamos las tablas de funciones y listas
    Tabla TablaFunc = tabla_crear(T_Funciones);
    Tabla TablaLists = tabla_crear(T_Listas);

    printf("Bienvenido al interprete de Funcion de Listas!\n");
    printf("La entrada debe ser en el formato: <funcion> <parametros>\n");
    printf("Las funciones disponibles son: deff, defl, apply, search, exit\n");
    char *entrada = malloc(sizeof(char) * 1000);
    fgets(entrada, 1000, stdin);
    entrada[strcspn(entrada, "\n")] = '\0';

    while (strcmp(entrada, "exit") != 0) {
        char *copia = malloc(strlen(entrada) + 1);
        if (copia == NULL) {
            perror("malloc");
            free(entrada);
            exit(1);
        }
        strcpy(copia, entrada); // hacemos una copia que el parser puede modificar

        parser(copia, TablaFunc, TablaLists);
        free(copia);

        fgets(entrada, 1000, stdin);
        entrada[strcspn(entrada, "\n")] = '\0';
    }

    free(entrada); //Liberamos la memoria de la entrada
    printf("Saliendo del interprete...\n");
    //Liberar memoria de las tablas y listas
    tabla_destruir(TablaFunc);
    tabla_destruir(TablaLists);
    return 0;
}
