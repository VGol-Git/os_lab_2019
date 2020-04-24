#!/bin/bash

while read i
do
sum=$[$sum + $i]
count=$[$count + 1]
done
sum=$[$sum / $count]

echo "arithmetic mean = $sum"
echo "count = $count"