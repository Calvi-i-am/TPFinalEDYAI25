#ifndef SENTENCIAS_H
#define SENTENCIAS_H

#define MAX_SIZE_BFS 10000 //Tamaño maximo del arbol de busqueda en search
#define MAX_SIZE_LENGHT 10 //Tamaño maximo de la longitud del arbol


#include "../Tablas/Tablas.h"

/**
 * Funcion que crea una lista en base a la entrada dada por consola.
 * Usa strtok para dividir la entrada y poder identificar su nombre y los nums.
 * Ademas, usa atoi para transformar los strings de numeros en integers.
 */
void defl(char *, Tabla );

/**
 * Funcion que crea una funcion de manera similar a defl, solo que
 * analiza cada subfuncion de la entrada, la busca en la tabla ya existente
 * y la agrega a la funcion a devolver
 * En caso de que una subfuncion no se haya definido previamente en la tabla
 * retorna vacio y libera toda memoria que haya utilizado
 */
void deff(char *,Tabla);


/**
 * Funcion recursiva que aplica una funcion compuesta a una lista.
 * 
 * Recibe una lista, una funcion y una tabla de funciones, ademas de dos indices,
 * inicio y final, que indican el rango de subfunciones a aplicar.
 * 
 * Nota: Estos indices (inicio y final) son necesarios para poder aplicar
 * la recursividad correctamente.
 */
Lista apply_compuestas(Lista, Funcion, Tabla, int, int);


/**
 * Funcion quue recibe una lista, una funcion y una tabla de funciones.
 * Retorna la lista resultante de aplicar la funcion a la lista.
 */
Lista apply_listas(Lista, Funcion, Tabla);



/**
 * Recibe una cadena y una tabla de listas.
 * La cadena contiene un nombre de lista o una lista en formato string.
 * Si es un nombre de lista, busca la lista en la tabla y la retorna.
 * Si es una lista en forma explicita, la crea y retorna.
 */
Lista string_a_lista(char *, Tabla);

/**
 * Recibe una entrada por consola en formato string de una funcion
 * y una lista. Primero, busca la funcion, en caso de que exista,
 * procede a evaluar la lista:
 *  -Si es un nombre de una lista, la busca en la tabla de listas y
 *   en caso de encontrarla, aplica la funcion a la lista
 *  -Si es en forma explicita, la cre para poder aplicarle la funcion
 *   y muestra el resultado en pantalla. NO se agrega la lista creada a la
 *   tabla de listas. 
 * Si todo sale bien, se imprime el resultado de la aplicacion
 * de la funcion a la lista.
 */
void apply(char*,Tabla, Tabla);





//Estructura auxiliar para el BFS de la funcion search
typedef struct {
    Funcion funcion; //Funcion aplicada para llegar a la lista de este nodo
    Lista lista; //Lista resultante de aplicar la funcion
    int padre_idx; //Facilita conseguir la secuencia de funciones
    int nivel;
} NodoBFS;

int tabla_buscar_lista(Lista*,Lista,int);

void search(char *, Tabla, Tabla);

#endif //SENTENCIAS_H