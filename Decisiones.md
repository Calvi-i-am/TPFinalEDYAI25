## Implementaciones

### Como podrian implementarse las listas?

Tuve varias ideas, pero con cada una me fui encontrando con problemas, y 
decidi quedarme con el "mal menor"

Lo que sabia es que, por lo menos, casi todas las funciones deberian tomar
O(1) tiempo, que no sean muy complejas de implementar o usar y que no ocupen
mucho espacio.

Tambien que solo tenia que modificar los extremos (notar q las 6 funciones solos
modifican los extremos de la lista)

Nota: en search, mi implementacion ademas requeriria una comparacion entre dos listas
de manera "rapida" para evitar tiempos de ejecucion complejos en la funcion search.
Ver el archivo correspondiente donde esto se explaya un poco mas.

- Primera idea: Array de numeros
    La "peor", ya que tiene un size fijo, ademas que Oi y Di se vuelven complejos (O(n)),
    y seria muy poco comprensible.

    Tambien pense en un array que tenga el indice inicial cerca del medio del espacio reservado,
    (osea, reservo 100 elementos y el array comienza del 25 al 75), pero seria un gasto de memoria
    ademas de tambien volverse raro a la vista.

- Segunda idea: string
    No es mala ya que se puede usar como clave para guardar en la tabla hash de listas,
    ademas de que serviria mucho a la hora de comparar. El problema es que se vuelve
    muy engorroso a la hora de operar en ellas, algo similar a la idea anterior

-Tercera idea: lista simplemente enlazada
    La mas obvia, tiene el problema de que Dd toma O(n) (se podria realizar en O(1) si fuera
    doblemente enlazada, pero seria mas costoso en la memoria), y que las comparaciones serian largas.
    Aun asi, es demasiado clara, facil de implementar y en cierta parte eficiente, asi que
    esta fue la idea ganadora

### Como podrian implementarse las funciones

Con las 6 funciones primitivas hechas, la idea era la siguiente:
    Cualquier funcion creada con "deff" seria una funcion compuesta,
    donde cada funcion de esta composicion se almacena en un array.
    Si se ve un "<>", se crearia una mini funcion que tendria
    la bandera de recursiva, para ejecutarla siempre y cuando
    el primer numero sea distinto que el segundo.

S