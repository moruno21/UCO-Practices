#!/bin/bash

#El -w fuerza a que se encuentren las palabras que se ponen entre comillas
echo -e "\n1) Mostrar los usuarios que tengan un intérprete de comandos válido asignado\n"
grep -w 'bash\|sh' /etc/passwd

echo -e "\n2) Mostrar los usuarios que tengan un home válido asignado\n"
grep -v nonexistent /etc/passwd

echo -e "\n3) Mostrar los usuarios y el nombre de su grupo en dos columnas\n"
echo "Usuario                              Grupo"
echo "=========================================="
while IFS=: read -r f1 f2 f3 f4 f5 f6 f7
do 
    printf "%20s\t\t%s\n" $f1 $f5
done < /etc/passwd | sort

# –i: no diferenciará entre mayúsculas y minúsculas.
# –w: fuerza que sólo encuentre palabras concretas.
# –v: selecciona las líneas que no coinciden.
# –n: muestra el número de la línea con las palabras de solicitadas.
# –h: elimina el prefijo del nombre del archivo Unix en la salida.
# –r: busca directorios recursivamente.
# –R: como -r pero sigue todos los enlaces simbólicos.
# –l: muestra sólo nombres de archivos con las líneas seleccionadas.
# –c: muestra sólo una cuenta por archivo de las líneas seleccionadas.
# –color: muestra los patrones coincidentes en colores.