#Crea un script que proporcione información acerca del uso de memoria del equipo. Puedes uti-
#lizar los comandos grep y sed para obtener la información necesaria del fichero /proc/meminfo.
#El script debe mostrar por pantalla la siguiente información:
#1. Memoria total.
#2. Memoria libre.
#3. Memoria disponible.
#4. Memoria en uso como caché de disco.
#5. Tamaño total de la memoria swap.
#6. Memoria swap libre.
#Además, el script recibirá un argumento númerico opcional. Este argumento, cuyo valor por
#defecto será 10, se utilizará para mostrar el Top-N procesos que más memoria están utilizando.
#Para ello, puedes utilizar la salida del comando ps aux.

#!/bin/bash

Nprocess=10

if [ $1 ]; then
    Nprocess=$1
fi

echo -n "Memoria total: " && cat /proc/meminfo | awk 'FNR == 1 {print $2 $3}' #FNR == 1 Cuando record number sea el 1, imprimimos $2 y $3
echo -n "Memoria libre: " && cat /proc/meminfo | awk 'FNR == 2 {print $2 $3}'
echo -n "Memoria disponible: " && cat /proc/meminfo | awk 'FNR == 3 {print $2 $3}'
echo -n "Memoria en uso como caché de disco: " && cat /proc/meminfo | awk 'FNR == 5 {print $2 $3}'
echo -n "Tamaño total de la memoria swap: " && cat /proc/meminfo | awk 'FNR == 15 {print $2 $3}'
echo -n "Memoria swap libre: " && cat /proc/meminfo | awk 'FNR == 16 {print $2 $3}'

echo -e "Top-$Nprocess procesos en uso de memoria."
echo -e "=============================================="
echo -e "Usuario \t\t % Uso \t Proceso"
echo -e "=============================================="
ps aux | awk 'NR>1{print $1," \t \t" $3, "\t" $11}' | head -n $Nprocess | sort -k 2 -n -r
#ps aux muestra todos los procesos en uso de memoria
#--sort -rss los ordena por rss
#head -n $Nprocess muestra los Nprocess primeros
#NR current record number in the total input stream