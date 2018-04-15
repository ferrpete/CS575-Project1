#!/bin/bash

# number of threads:
for t in 1 2 4 6 8
do
	echo NUMT = $t
	# number of subdivisions:
	for s in 2 4 8 16 32 64 128 256 512 1024 2048 3072 4096
	# for s in 4
	do
		echo NUMNODES = $s
		g++ -DNUMNODES=$s -DNUMT=$t Project1.cpp Project1.h Height.cpp Weight.cpp -o Project1 -lm -fopenmp
		./Project1
	done
done
