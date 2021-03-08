#!/bin/bash

read -p "Introduzca un numero t.q. 1 <= x < 10: " x

if [ $x -ge 1 ];
then
    if [ $x -lt 10 ];
    then
        echo "El número está en el rango"
    else
        echo "El número no está en el rango"
    fi
else
    echo "El número no está en el rango"
fi
