#!/bin/bash

for i in $@
do
sum=$[$sum + $i]
done
sum=$[$sum / $#]

echo "arithmetic mean = $sum"
echo "count = $#"