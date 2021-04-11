# Este programa copia ficheros de la carpeta origen a la carpeta destino
# Como mucho se harán n copias. Si se excede, se borra la mas antigua (la 1)
# NOTA: La carpeta destino no existe. Debe de crearse externamente ya que el script no se encarga de crearla
#Ejemplo de ejecución: ./ej3.sh carpeta_origen carpeta_destino 4


#!/bin/bash

if [ $# -ne 3 ] || [ ! -d $1 ] || [ ! -d $2 ] # $# almacena el numero de argumentos pasados por línea de comandos (sin incluir el 0)
then
    echo "Formato incorrecto. Ejemplo: ./ejercicio.sh origen destino 10"
    exit
fi

numCarpetas=$(ls $2 | wc -l) #Cuenta todos los ficheros que hay en el directorio

if [ $numCarpetas -lt $3 ] #Entramos siempre que haya menos carpetas creadas del limite
then
    nuevaCarpeta=$(($numCarpetas+1)) #Por ejemplo, si tenemos 3 carpetas, crearemos la carpeta 4
    mkdir $2/$nuevaCarpeta #Creamos la carpeta
    for a in $(ls $1) #Iteramos todos los ficheros que queramos copiar
    do
        if [ -f $a ] #Comprobamos que sea un fichero
        then
            cp $a $2/$nuevaCarpeta #Copiamos el fichero a la carpeta que creamos al principio del condicional
        fi
    done
else
    
    rm -r $2/1 #Borramos la carpeta más antigua
    mkdir $2/1 #La volvemos a crear pero está vacía
    for y in $(seq 2 $3 )
    do
        mv $2/$y/* "$2/$(($y-1))" #Vamos copiando de la 2 a la 1, de la 3 a la 2, y así sucesivamente
    done
    
    for a in $(ls $1) #Iteramos el contenido de la carpeta actual
    do
        if [ -f $a ] #Comprobamos que a sea un fichero
        then
            cp $a $2/$3 #Copiamos a la ultima carpeta de todas el contenido de nuestro fichero
        fi
    done
fi