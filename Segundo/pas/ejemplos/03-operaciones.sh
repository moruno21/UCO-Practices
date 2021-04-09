#!/bin/bash
read -p "Numero 1: " num1
read -p "Numero 2: " num2

echo "Suma: $[$num1 + $num2]"
echo "Resta: $(($num1 - $num2))"
echo "Multiplicación: $(($num1 * $num2))"
echo "División: $(($num1 / $num2))"
echo "Módulo: $(($num1 % $num2))"



