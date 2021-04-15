#!/bin/bash

who | awk '{printf "El usuario " $1 " lleva conectado desde las " $4 " y lleva ausente " $5 "\n" }'

# who nos devuelve quien esta logeado:
# usuario :0           2021-04-12 09:20 (:0)
# con el comando awk lo que hacemos es capturar la salida anterior en variables, siendo:
# $1 usuario        nombre de usuario
# $2 :0             segun la documentacion es la línea de terminal (terminal line)
# $3 2021-04-12     fecha de conexion
# $4 09:20          hora de conexion
# $5 (:0)           tiempo inactivo