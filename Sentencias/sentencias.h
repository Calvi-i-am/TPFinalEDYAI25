#include "Funciones.h"
#include "listas.h"
#include "tablas.h"

/**
 * Funcion que crea una lista en base a la entrada dada por consola.
 * Usa strtok para dividir la entrada y poder identificar su nombre y los nums.
 * Ademas, usa atoi para transformar los strings de numeros en integers.
 */
void defl(char *, Tabla *);


/**
 * Determina si una funcion ya pertenece a la tabla de funciones
 */
int tabla_buscar_f(char *, Tabla*);