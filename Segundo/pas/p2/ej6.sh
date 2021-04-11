#Desarolla un script que muestre por pantalla información acerca de los sistemas de archivos que hay montados. Para ello, puedes utilizar el comando df. La información que se mostrará será la siguiente:
#1. Sistema de ficheros.
#2. Punto de montaje.
#3. Tamaño.
#4. Espacio libre.
#5. Porcentaje de uso.
#La salida deberá estar en un formato similar al que se muestra en el siguiente ejemplo:


#!/bin/bash

df | sed -r -n -e '2,$s/^([a-Z0-9/:\\]+)[ ]+([0-9]+)[ ]+([0-9]+)[ ]+([0-9]+)[ ]+([0-9]+%)[ ]+([a-Z0-9/]+)/El sistema de ficheros \1, esta montado en \6, tiene un tamaño de \2 de los cuales se estan usando \3 que representan un porcentaje de \5 del total. Quedan libres \4./p'
