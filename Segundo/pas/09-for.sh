#!/bin/bash

let sum=0
for num in 1 2 3 4 5
do
    let "sum = $sum + $num"
done
echo $sum