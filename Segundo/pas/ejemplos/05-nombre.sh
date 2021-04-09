#!/bin/bash


read -p "Introduzca su nombre de usuario: " nombre

if [ $nombre == $USER ] 
then
    echo "Bienvenido $nombre"
else
    echo "Eres un impostor!"
fi