#Desarolla un script que muestre por pantalla información acerca de los sistemas de archivos que hay montados. Para ello, puedes utilizar el comando df. La información que se mostrará será la siguiente:
#1. Sistema de ficheros.
#2. Punto de montaje.
#3. Tamaño.
#4. Espacio libre.
#5. Porcentaje de uso.
#La salida deberá estar en un formato similar al que se muestra en el siguiente ejemplo:


#!/bin/bash

df | sed -r -n -e '2,$s/^([a-Z0-9/:]+)[ ]+([0-9]+)[ ]+([0-9]+)[ ]+([0-9]+)[ ]+([0-9]+%)[ ]+([a-Z0-9/]+)/El sistema de ficheros \1, esta montado en \6, tiene un tamaño de \2 de los cuales se estan usando \3 que representan un porcentaje de \5 del total. Quedan libres \4./p'

# -r uso de ERE en vez de BRE
# -n hace que no se impriman por pantalla las líneas procesadas
# -e indican qu estamos pasando comandos por la línea de comandos y no a través de un archivo

# p Imprime las líneas direccionadas
# s Sustituir una expresión por otra sobre las líneas seleccionadas
# d Borra las líneas direccionadas

# 2, $s indica que se efectua de la línea 2 a la última
# Si pusieramos s3, sería sustituir la tercera coincidencia de la primera línea
# Si pusieramos 3s, sería sustituir la primera coincidencia de la tercera línea
# ^ empareja con el principio de la línea -> ^O
# $ empareja con el final de una línea -> o$
# [ ] indican una lista de caracteres posibles
# [^ ] indican una lista de caracteres no posibles

# Bandera n reemplaza solo la n-ésima ocurrencia
# Bandera g reemplaza todas las ocurrencias
# Bandera p forzar a imprimir la línea (cuando usamos -n)''