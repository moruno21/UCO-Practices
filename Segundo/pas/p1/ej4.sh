#Menu para personalizar el prompt
#Ejemplo de ejecución: ./ej4.sh

#!/bin/bash

menu(){
    echo "=== Personalización del prompt"
    echo "Selecciona la opcion a añadir"
    echo "1. Nombre de usuario"
    echo "2. Nombre de host"
    echo "3. Ruta completa"
    echo "4. Última parte de la ruta"
    echo "5. Hora"
    echo "6. Fecha"
    echo "7. Cadena literal"
    echo "8. Añadir color y estilo"
    echo "9. Cancelar"
    echo "0. Confirmar"
    read opcion  
}

datos=""
menu
while [ $opcion -ne 9 ]
do
    case $opcion in
        1)
            datos=$datos"\u"
            ;;
        2)
            datos=$datos"@\h"
            ;;
        3)
            datos=$datos"\w"
            ;;
        4)
            datos=$datos"\W"
            ;;
        5)
            datos=$datos"\A"
            ;;
        6)
            datos=$datos"\d"
            ;;
        7)
            read cadena
            datos=$datos" $cadena"
            ;;
        8)
            echo "- Tipo de fuente -"
            echo "1. Normal"
            echo "2. Negrita"
            echo "3. Subrayado"
            read opcionfuente

            echo "- Color de fuente -"
            echo "1. Negro"
            echo "2. Rojo"
            echo "3. Verde"
            echo "4. Amarillo"
            echo "5. Azul"
            echo "6. Blanco"
            read opcioncolor

            echo "- Color de fondo -"
            echo "1. Negro"
            echo "2. Rojo"
            echo "3. Verde"
            echo "4. Amarillo"
            echo "5. Azul"
            echo "6. Blanco"
            read opcionfondo

            datos=$datos"\e[" #ponemos el \e[ para iniciar la edicion del formato

            #primero el tipo de fuente
            if [ $opcionfuente -eq 1 ]
            then
                datos=$datos"0"
            elif [ $opcionfuente -eq 2 ]
            then
                datos=$datos"1"
            else
                datos=$datos"4"
            fi

            #punto y coma
            datos=$datos";"

            #color del texto
            if [ $opcioncolor -eq 1 ]
            then
                datos=$datos"30"
            elif [ $opcioncolor -eq 2 ]
            then
                datos=$datos"31"
            elif [ $opcioncolor -eq 3 ]
            then
                datos=$datos"32"
            elif [ $opcioncolor -eq 4 ]
            then
                datos=$datos"33"
            elif [ $opcioncolor -eq 5 ]
            then
                datos=$datos"34"
            else
                datos=$datos"37"
            fi

            #punto y coma
            datos=$datos";"

            #color de fondo
            if [ $opcionfondo -eq 1 ]
            then
                datos=$datos"40m"
            elif [ $opcionfondo -eq 2 ]
            then
                datos=$datos"41m"
            elif [ $opcionfondo -eq 3 ]
            then
                datos=$datos"42m"
            elif [ $opcionfondo -eq 4 ]
            then
                datos=$datos"43m"
            elif [ $opcionfondo -eq 5 ]
            then
                datos=$datos"44m"
            else
                datos=$datos"47m"
            fi

            ;;

        0)
            PROMPT_COMMAND="PS1='$datos';unset PROMPT_COMMAND" bash
            exit 1
            ;;
        *)
            echo "Opción no válida, inténtelo de nuevo"
            ;;
    esac
    echo "PROMPT ACTUAL: $datos"
    menu
done   

        