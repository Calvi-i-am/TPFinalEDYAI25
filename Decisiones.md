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
    representada como un array de funciones que previamente ya fueron
    definidas. En caso de que a la hora de leer la declaracion de 
    una funcion, nos encontremos con "<", se agrega una bandera al array
    que indica que las siguientes funciones (hasta encontrar el ">")
    se deben repetir hasta cumplir la condicion de repeticion.


El como llevaria esto a una representacion que contenga todo seria
una estructura tal que:
- Su nombre sea usado como key para el diccionario de funciones (tabla hash),
- En caso de ser primitiva (que nunca va a pasar a la hora de usar deff),
  tenga el puntero a la funcion primitiva nombrada
- En caso contrario, un array donde contenga tanto las funciones que vaya leyendo,
  como tambien las banderas de repeticion ya nombradas.

    Algo asi:

    Input: deff f4 = 0i 0i <Sd Dd> 0d

    Nuestra funcion tendria:

    nombre = "f4" (string)
    Funciones[0] = Oi
    Funciones[1] = Oi
    Funciones[2] = < (osea, aqui comienza la repeticion sii se cumpla la coindicion)
    Funciones[3] = Sd
    Funciones[4] = Dd
    Funciones[5] = > (aqui termina la repeticion)
    Funciones[6] = Od
    Funciones[7] = NULL

    NULL representa el final de la lista.

### Como implementar apply

Ya con las listas y las funciones implementadas, apply no deberia llevar muchas complicaciones

Dada una funcion y una lista, se busca si la funcion pertenece a la tabla de funciones,
en caso valido, creo la lista a evaluar, y hago lo siguiente:
- Si la funcion es primitiva, la evaluo y retorno el resultado, mostrandolo en pantalla
- Si es compuesta, uso un indice como cabezal para ir aplicando cada funcion del array
a la lista, hasta llegar al final y retornando la lista resultante.
  En este caso, si el cabezal se para en un "<" y la condicion vale (primer numero distinto
  del ultimo), ejecuta la repeticion hasta encontrar el ">" (esto lo hace de manera recursiva
  para preveer por si hay una repeticion dentro de otra).

#### Como determinar si termina la llamada?

Esto es imposible de determinar para toda posible llamada, y al recibir la consigna
de que no es necesario que toda llamada termine, bastaria con no analizar estos casos

Aun asi, al alcanzar limites ilogicos en la funcion, se indicara que la funcion posiblemente
no termine, por lo que se puede proceder con:
  - Un simple aviso y recomendar que se corte la ejecucion del programa, o
  - Cortar con la llamada del apply y ejecutar las siguientes sentencias
