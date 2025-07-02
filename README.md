# TPFinalEDYAI25
Trabajo practico final para la materia Estructuras de Datos y Algoritmos I (2025), por Alvaro Cabrera

## Objetivo y motivaciones
El objetivo principal de este proyecto es realizar un interprete de funciones de listas, usando,
como herramienta princial, el lenguaje de C.

Para esto, se usa un entorno iterativo donde se podra definir listas y funciones de listas, ademas
de poder aplicar funciones (previamente definidas) a listas, como poder realizar una 
funcion "search" (explicacion de search todavia no creada)

## Consideraciones
- Se espera que una lista valida sea del tipo: [1,2,3] o [1 , 2 , 3]
  Nota: No importan los espacios entre los numeros o comas, sino que cada numero 
  este separado por una coma

  Ejemplo: [1 0, 5 , 4] se interpreta como 10,5,4, ya que entre entre el 1 y el 0 no hay comas

  Enfatizar en que una lista bien definida usa corchetes ( "[]" ),
  no se admitiran listas que usen parentesis ( "()" ) o llaves ( "{}" ).

- Las listas solo pueden ser formadas por numeros naturales (por def.)

- Todo valor no natural ingresado es truncado hacia abajo, ejemplo: 7.45 --> 7

- No existe limite de que tan grande puede ser una lista (exceptuando limites fisicos de memoria),
  y es valido definir listas vacias como [].

