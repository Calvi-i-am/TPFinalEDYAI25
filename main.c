#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Parser/parser.h"

int main(){

    //Inicializamos las tablas de funciones y listas
    Tabla TablaFunc = tabla_crear(T_Funciones);
    Tabla TablaLists = tabla_crear(T_Listas);

    printf("Bienvenido al interprete de Funcion de Listas!\n");
    printf("La entrada debe ser en el formato: <funcion> <parametros>\n");
    printf("Las funciones disponibles son: deff, defl, apply, search\n");
    printf("Tambien se puede ingresar exit para salir del programa\n\n");

    char * entrada = malloc(sizeof(char) * 1000);
    fgets(entrada, 1000, stdin); //fgets y no scanf para evitar problemas con espacios
    entrada[strcspn(entrada, "\n")] = '\0';
    while(strcmp(entrada, "exit") != 0){
        parser(entrada, TablaFunc, TablaLists);
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