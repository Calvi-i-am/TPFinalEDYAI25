#ifndef SENTENCIAS_H
#define SENTENCIAS_H

#include "../Tablas/tablas.h"

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

Lista apply_compuestas(Lista, Funcion, Tabla, int, int);

Lista apply_listas(Lista, Funcion, Tabla);

/**
 * Recibe una entrada por consola en formato string de una funcion
 * y una lista. Primero, busca la funcion, en caso de que existe, ve
 * si la lista recibida esta en formato de nombre o explicita:
 *  -Si es un nombre de una lista, la busca en la tabla de listas y
 *   en caso de encontrarla, aplica la funcion a la lista
 *  -Si es en forma explicita, la cre para poder aplicarle la funcion
 *   y muestra el resultado en pantalla. NO se agrega la lista creada a la
 *   tabla de listas. 
 */
Lista apply(char*,Tabla, Tabla);


#endif //SENTENCIAS_H