##Proyecto integrador:
## Ordenador de canciones 
Este proyecto cosnsite en un programa de un directorio de canciones, en donde a travez de un formato txt que le damos al programa, se toman los datos de esta misma y se crean objetos que son ordenados de manera alfabetica.

Ademas de eso se agregaron metodos para buscar,eliminar y agregar canciones a travez de funciones programadas en sus clases correspondientes. 

## Primer avance 
En este primer avance se implento:
- Clases como canciones.h y sorts.h para poder crear canciones y hacer gestiones de las listas de estas mismas.
- Lectura de un archivo txt donde se almacenan los datos de las canciones.
- Funcion de busqueda atravez del nombre de la cancion.
- Ordenamiento por diferentes atributos.
-Implementacion de metodos de ordenamiento como merge y de busqueda binaria.
Para este primer avance se decidio utilizar Merge sort para el ordenamiento dependiendo de los atributos escogidos.
Debido a la cantidad y tamaño de datos el merge sort es la mejor opcion debido a su complejidad de 0(n log n) en el mejor y peor de los casos, lo que es ideal para listas grandes y desordenadas.Tambien la estabilidad que proporciona con la comparacion de valores iguales es de gran ayuda ya que con los datos que hay en la lista txt hay repeticiones en diferentes atributos pero apesar de eso el Mergesort mantiene el mismo orden relativo que habia en la lista txt.

En conclusion, el alogoritmo de Mergesort fue el de mejor ayuda por su rendimiento constante, tambien por la mejor complejidad temporal a comparacion con otros algoritmos en sus peores y mejores casos.

### Consideraciones 
Se recomienda siempre al ingresar un string se empiece con mayusculas y siga con minusculas. Ejemplo: nombre de cancion: Mi luz.

## Segundo avance

En este avance el proyecto fue modificado en su funcionalidad y estructura, el principal cambio que se le hizo fue omitir el uso de listas y vectores, y se remplazó por el uso una estructura de un árbol AVL. El programa ahora consiste en un directorio en donde atravez de un archivo txt se extraen canciones para después ser agregadas al árbol pero ordenadas de manera alfabéticamente, también se incluyeron funciones de buscar, eliminar y agregar canciones extras al gusto del usuario.

La decisión de usar la estructura de un árbol AVL es que estos nos benefician bastante por el tamaño de datos que tenemos y la manera en que pueden escalar por la decisión del usuario. Además de los siguientes beneficios que nos aporta son:

-Debido a su capacidad de autobalanceo, las operaciones de búsqueda, eliminación y agregación sean eficientes manteniéndose en un grado de complejidad O(log n) incluso en el peor de sus casos.
-Tiempo de respuesta rápida en sus operaciones en comparación con otros algoritmos, gracias a su capacidad de realizar modificaciones dinámicas.
-Funciones dinámicas que ayudan a que el árbol en todo momento funcione de una manera fluida a pesar del crecimiento que pueda tener.

## Tercer avance

En este avance el proyecto fue modificado, implementando una función que permite la escritura de archivos en este caso en nuestro archilo lista_canciones.txt para poder guardar los cmabios que hay al momento de agregar canciones al arbol AVL. A su vez en este avance se agregaron los analisis de complejidad de todas las funciones en el arbol AVL especificando que hace cada una, su nombre y grado de complejidad que cada una emplea. 

Tambien se realizaron correciones para al momento de ingresar datos, ahora en los atributos que son float o int se da una especificaion breve de como debe de ser.









