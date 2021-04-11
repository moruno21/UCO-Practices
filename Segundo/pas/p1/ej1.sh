#Script que muestra por pantalla los ficheros de la carpeta que especifiquemos por linea de comandos
#Muestra el número de caracteres del nombre del fichero
#De los fichero con longitud impar, muestra una serie de propiedades
#Ejemplo de ejecución: ./ej1.sh nombre_carpeta

#!/bin/bash 
# $1 se refiere al primer argumento de la linea
if [ -d $1 ]
then
    for x in $(find $1) 
    do
        nombre_sin_ruta=$(basename $x) #basename devuelve el nombre del fichero sin la ruta donde se encuentra
        echo -n "$nombre_sin_ruta <- "	
        caracteres=$(echo -n $nombre_sin_ruta | wc -m )	
        if [ $caracteres -eq 1 ] #comparacion singular o plural
        then
            echo "$caracteres caracter"
        else
            echo "$caracteres caracteres"
        fi
            
    done
fi 

if [ -d $1 ]
then
    for x in $(find $1) 
    do
        nombre_sin_ruta=$(basename $x) #basename para obtener el nombre del fichero
        carpeta=$(dirname $x)	 #devuelve la carpeta donde se aloja el fichero
        ruta_absoluta=$(pwd $carpeta) #pwd para devolver la ruta absoluta de la carpeta				
        caracteres=$(echo -n $nombre_sin_ruta | wc -m )	
            
        let modulo=$caracteres%2 #Calculo modulo de caracteres para saber si es impar o par	
        if [ $modulo != 0 ]
        then	
            #mirando el man stat se pueden sacar todos.
            i_nodo=$(stat -c "i-nodo %i" $x)
            bytes=$(stat -c "%s" $x)
            kilobytes=$[$bytes/1024]
            permiso=$(stat -c "permisos: %a" $x)
            usuario=$(stat -c "%U" $x)
            grupo_usuario=$(stat -c "%G" $x)
            echo "$nombre_sin_ruta, $ruta_absoluta, $i_nodo, $bytes bytes ($kilobytes K), $permiso, $usuario : $grupo_usuario"
        fi	
    done
fi 
