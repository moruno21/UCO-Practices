#Script que recibe 2 parametros, un directorio y un numero N
#Divide en N grupos de igual tamaño los ficheros que se encuentran en el directorio
#Ejemplo de ejecución: ./ej2.sh nombre_carpeta 4

#!/bin/bash

if [ -d $1 ] && [ $2 -gt 0 ] #1 debe ser un directorio y 2 debe ser > 0
then
	echo "Formato de entrada correcto"

	for a in $(ls $1) #Contamos el numero de archivos que hay en la carpeta
	do
		if [ -f $a ] #Comprobamos que a sea un fichero
		then
			let "x = $x + 1"
		fi
	done

	echo "Hay $x ficheros en $1"

	if [ $2 -gt $x ] #Si el argumento 2 es mayor que el número de archivos, no podremos organizar los archivos en grupos
	then
		echo "Error, el numero de archivos es menor que el numero de grupos"
		exit
	fi

	if [ $[x%$2] -ne 0 ] #Si el número de archivos no es divisible entre el argumento 2, no podremos organizar los archivos en grupos
	then
		echo "No se pueden dividir $x ficheros en $2 partes iguales"
		exit
	fi

else
	echo "Formato de entrada incorrecto"
	exit
fi

let size=$[x/${2}]
echo "El tamaño de grupo es $size"

#echo "lo que hay en el directorio es"
#ls $1 #ls ya muestra el contenido ordenado alfabeticamente

mkdir groups #Creamos la carpeta donde agruparemos
for var in $( seq $2 )
do
	mkdir "groups/group$var" #Haremos N grupos, por lo tanto crearemos N carpetas
done

x=1 #Variable que usaremos para copiar los archivos a los grupos
for b in $(ls $1)
do
	if [ -f $b ]
	then
		cp $b groups/group$x #Copiamos el fichero a su correspondiente carpeta
		if [ $(find groups/group$x -maxdepth 1 -type f | wc -l) -eq $size ] #Si llenamos una carpeta, modificamos x para seguir añadiendo ficheros a otra carpeta
		then
			let "x = $x + 1" #Aumentamos el valor de x
		fi
	fi
done