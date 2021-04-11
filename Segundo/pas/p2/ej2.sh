#!/bin/bash

echo -e "\n1) Mostrar los usuarios que tengan un intérprete de comandos válido asignado\n"
grep -w 'bash\|sh' /etc/passwd

echo -e "\n2) Mostrar los usuarios que tengan un home válido asignado\n"
grep -v nonexistent /etc/passwd

echo -e "\n3) Mostrar los usuarios y el nombre de su grupo en dos columnas\n"
echo "Usuario                              Grupo"
echo "=========================================="
while IFS=: read -r f1 f2 f3 f4 f5 f6 f7
do 
    printf "%20s %20s\n" $f1 $f5
done < /etc/passwd