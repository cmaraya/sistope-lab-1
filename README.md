# sistope-lab-1
Laboratorio 1 para el ramo de SISTOPE 2_2020
Autores: Catalina Araya y Ekaterina Cornejo

El enunciado es el siguiente: 
Una secuencia de ADN, secuencia de nucle ́otidos o  ̈secuencia gen ́etica ̈es una sucesi ́on de letras que rep-
resenta la estructura primaria de una mol ́ecula real o hipot ́etica de ADN o banda, con la capacidad de
transportar informacion.

Las posibles letras son A, C, G, y T, que simbolizan las cuatro subunidades de nucle ́otidos de una banda
de ADN - adenina, citosina, guanina, timina, que son bases covalentemente ligadas a cadenas fosf ́oricas. Una
sucesi ́on de cualquier n ́umero de nucle ́otidos mayor a cuatro es posible de llamarse una secuencia.
Es decir, se busca encontrar una sucesi ́on de  ́estos nucle ́otidos en distintos archivos de texto.
A continuaci ́on un ejemplo del archivo de entrada y un ejemplo de sucesi ́on.

Archivo de entrada: cadena de ejemplo AAATTGCGCVGTAAGCTTGACGGACGTTAGGCAGTCA

En el contenido de este archivo, se debe buscar l ́ınea a l ́ınea si existe una sucesi ́on que cumpla con la que
busco.

Un ejemplo de sucesi ́on: AAAA, TTTA, CATT, etc.
Es decir que en la primera linea busco si se encuentra AAAA, si es verdadero, escribo en un archivo la
linea revisada y un SI a su lado, en caso contrario, se escribe NO. Este paso se repite hasta recorrer todo el
archivo.

V. Enunciado

Se solicitan dos programas. Uno para realizar la tarea de comparaci ́on y el otro para coordinar los
procesos y as ́ı juntar los resultados.

V.A. Programa comparador
El primer programa debe realizar la tarea de encontrar las coincidencias de las cadenas en una secci ́on de
un archivo, para esto se le debe indicar el archivo a ocupar, desde que posici ́on de cursor debe comenzar a
leer este archivo, la cadena a encontrar, en cuantas cadenas (lineas) debe hacer la comparaci ́on y un numero
identificador.
Los resultados de estas comparaciones deben guardarse en un archivo de salida, este archivo debe tener
un nombre estandarizado, siguiendo el siguiente patron:
rp <cadena a buscar> <numero de proceso>.txt
El prefijo rp , de resultado parcial, junto con el resto del patr ́on es para que el programa coordinador
pueda encontrarlos sin problemas.

V.B. Programa coordinador
El segundo programa es el encargado de coordinar las ejecuciones de los procesos del programa comparador.
Es el que calcula e indica cuales lineas debe leer cada uno de los procesos, para esto se le debe indicar
el archivo a leer, el numero de procesos y el largo de las cadenas a leer, de este modo al conocer el largo
del archivo, el programa coordinador puede calcular la posici ́on del cursor del archivo para pasarlo como
argumento a los programas coordinadores.
Finalmente cuando todos los procesos comparadores hayan terminado, el programa coordinador debe
reunir los resultados en un solo archivo de salida, para la uni ́on de los archivos. Se recomienda usar la
funci ́on fread, indic ́andole el tama ̃no completo del archivo y con fwrite escribir esta informacion al final del
archivo de salida de resultados completo.
Del mismo modo que el programa anterior se pide un nombre estandarizado para el archivo de resultados
completo, este debe seguir el siguiente patron:
rc <cadena a buscar>.txt
A continuacion un ejemplo del archivo de salida:
Ejemplo del archivo de salida:

Figure 3. Archivo de salida

Las entradas del programa coordinador deben ser utilizando getopt, con la siguiente lista de entradas:

• -i: nombre del archivo de entrada
• -n: numero de procesos de tipo comparador
• -c: cantidad de l ́ıneas de archivo de entrada.
• -p: cadena a buscar
• -d: bandera que indica si se deben mostrar los resultados por pantalla

Se mantiene el orden en que se ingresan las variables.

Figure 4. Como recibir los par ́ametros de entrada

V.C. Par ́ametros de entrada
