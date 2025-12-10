//Cabrera Alvaro, 2025.
//--------------------------

//Definicion de funciones auxiliares y del parser

//--------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Sentencias/Sentencias.h"

/**
 * Toma una cadena de entrada, la tabla de funciones y la tabla de listas,
 * y procesa la cadena de entrada de la siguiente manera:
 *  -Ignora espacios al principio
 *  -Toma el nombre de la funcion (hasta el primer espacio)
 *  -Toma el resto de la secuencia
 *   (esto seria hasta ';' o '}' (en caso de search) o hasta el final de la cadena)
 *  -Dependiendo del nombre de la funcion, llama a la funcion correspondiente
 *  -Avanza la cadena hasta la siguiente subsecuencia
 */
void parser(char*, Tabla, Tabla);