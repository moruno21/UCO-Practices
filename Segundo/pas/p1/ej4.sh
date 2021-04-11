#Script que abre un menu para poder personalizar el prompt 


#!/bin/bash
opcion=1
while [ $opcion -ne 0 ] 			#hacemos un bucle para el menu
do
	echo "Seleccione un opcion" 
	echo "1.Nombre usuario"
	echo "2.Nombre del host"
	echo "3.Ruta completa"
	echo "4.Ultima parte de la ruta"
	echo "5.Hora"
	echo "6.Fecha"
	echo "7.Cadena literal"
	echo "8.Confimar"
	echo "0.Salir"

	read opcion # lee por terminal y lo guarda en la variable opcion

	case $opcion in

		1)	export var="\u";; #vamos guardando las opciones (concatenandolas)
		2)	export var="\h";;
		3)	export var="\w";;
		4)	export var="\W";;
		5)	export var="\t";;
		6)	export var="\d";;
		7)	read var;;
		8)	PROMPT_COMMAND="PS1='$PS1'; unset PROMPT_COMMAND" bash;; # ejecutamos lo que llevamos

		#esac (case al reves) como if y fi, es lo que se ejecuta al elegir una opcion del case
	esac
		PS1="$PS1$var"		#como al elegir un numero hacemos export var, vamos concatenando lo que tiene var a cada vez en PS1
		echo "PROMT ACTUAL: $PS1"
done

#COMANDOS DEL PS1

#    \a un caracter ASCII de ring
#     \d la fecha actual en formato "dia_sem mes día", "dom nov 18"
#     \e un caracter ASCII de escape
#     \h el nombre del equipo hasta el primer ., ejemplo linuxtotal de linuxtotal.com.mx
#     \H el nombre del equipo
#     \n nueva línea
#     \r retorno de carro, enter
#     \s el nombre del shell
#     \t el tiempo actual en formato de 24 horas HH:MM:SS
#     \T el tiempo actual en formato de 12 horas HH:MM:SS
#     \@ el tiempo actual en formaro de 12 horas con am/pm
#     \u el usuario actual
#     \v la version de bash
#     \V el número de release de batch, versión + parche
#     \w el directorio de trabajo actual, path
#     \W el nombre del directorio actual
#     \! el número en el historial del comando
#     \# el número de comando de este comando
#     \$ si el usuario es root (UID=0) se indica un '#', un usuario normal '$'
#     \\ diagonal
#     \[ inicio de una secuencia de caracteres no imprimibles
#     \] fin de la secuencia de caracteres no imprimibles