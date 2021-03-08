#!/bin/bash

read -p "Introduzca el nombre del fichero: " fichero

if [ -f $fichero ];
then
    cp $fichero "$fichero.bak_$(date +%d-%m-%y)"
    echo "Se ha hecho una copia del fichero!"
else
    echo "El fichero no existe!"
    exit 1
fi