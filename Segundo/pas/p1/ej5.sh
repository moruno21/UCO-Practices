#El contenido de hash.txt es el hash de una contraseña de entre 1 y 5 caracteres en hexadecimal
#El ejercicio se trata de averiguar cual es la contraseña a partir de dicho hash
#Ejemplo de ejecución: ./ej5.sh
#El fichero hash.txt es utilizado por este ejercicio


#!/bin/bash
hash="$(cat "hash.txt")" #cat muestra el contenido de hash.txt. Guardamos el hash en hash

#echo {{0..9},{A..F}}
comb=16 #Hay 16 posibles combinaciones (hexadecimal)


# Combinaciones posibles con 1 solo caracter

echo "Probando las $comb combinaciones de longitud 1"
for i in $(eval echo {{0..9},{A..F}}) #Vamos comprobando todas las combinaciones de 1 caracter
do
    #echo "i = $i"
    try="$(echo $i | sha256sum)" #Guardamos en try el hash de la cadena i la cual estamos probando
    if [ "$try" == "$hash" ] #Comprobamos si el hash de la cadena que estamos probando es el hash que estamos buscando
    then 
        echo "Se ha encontrado la contraseña: $i" #Si los hash coinciden, entonces hemos encontrado la contraseña
        exit
    fi
done

let "comb = $comb * 16"


# Combinaciones posibles con 2 caracteres

echo "Probando las $comb combinaciones de longitud 2"
for i in $(eval echo {{0..9},{A..F}}{{0..9},{A..F}}) #Vamos probando todas las combinaciones de 2 caracteres
do
    #echo "i = $i"
    try="$(echo $i | sha256sum)"
    if [ "$try" == "$hash" ]
    then 
        echo "Se ha encontrado la contraseña: $i"
        exit
    fi
done

let "comb = $comb * 16"


# Combinaciones posibles con 3 caracteres

echo "Probando las $comb combinaciones de longitud 3"
for i in $(eval echo {{0..9},{A..F}}{{0..9},{A..F}}{{0..9},{A..F}})
do
    #echo "i = $i"
    try="$(echo $i | sha256sum)"
    if [ "$try" == "$hash" ]
    then 
        echo "Se ha encontrado la contraseña: $i"
        exit
    fi
done

let "comb = $comb * 16"


# Combinaciones posibles con 4 caracteres

echo "Probando las $comb combinaciones de longitud 4"
for i in $(eval echo {{0..9},{A..F}}{{0..9},{A..F}}{{0..9},{A..F}}{{0..9},{A..F}})
do
    #echo "i = $i"
    try="$(echo $i | sha256sum)"
    if [ "$try" == "$hash" ]
    then 
        echo "Se ha encontrado la contraseña: $i"
        exit
    fi
done


let "comb = $comb * 16"


# Combinaciones posibles con 5 caracteres

echo "Probando las $comb combinaciones de longitud 5"
for i in $(eval echo {{0..9},{A..F}}{{0..9},{A..F}}{{0..9},{A..F}}{{0..9},{A..F}}{{0..9},{A..F}})
do
    #echo "i = $i"
    try="$(echo $i | sha256sum)"
    if [ "$try" == "$hash" ]
    then 
        echo "Se ha encontrado la contraseña: $i"
        exit
    fi
done