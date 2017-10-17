#!/bin/bash

read x y

i=0
j=0

while [ $i -lt $x ]
do
	j=0
	while [ $j -lt $y ]
	do
		printf "0 " >> 2_map.mpf
		((++j))
	done
	printf "\n" >> 2_map.mpf
	((++i))
done
