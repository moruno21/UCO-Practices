#El script lee el fichero que le pasemos como argumento, y resuelve la ip de las direcciones que contiene dicho fichero
#Ejemplo de ejecución: ./ej6.sh direcciones.txt
#NOTA: Usar para la ejecucion el fichero direcciones.txt que se proporciona


#!/bin/bash

if [ $# -ne 1 ] #El numero de argumentos pasados por terminal debe de ser obligatoriamente 1
then
	echo "El script debe recibir un argumento obligatoriamente."
	exit 1
fi

while read direccion #Leemos línea por línea el fichero que pasamos por línea de argumentos
do
	ip=$(dig $direccion +short) #Comando para resolver la ip
	echo -e "$ip\t\t\t$direccion" #Imprimimos por pantalla la ip con su correspondiente dirección
done < $1 #Esto se usa cuando hacemos un bucle para leer un fichero (contando con que el fichero está en $1)