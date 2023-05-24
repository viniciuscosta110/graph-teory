#!/bin/bash

# Binários
bellman_ford=./bellman_ford.bin

echo "Testando algoritmo de Bellman-Ford"
for i in instances/*.mtx
do
	echo -e "\e[33mInstância $i\e[0m";
	graph=$($bellman_ford -f $i);
	
	echo $graph;

	if [ $? -eq 0 ]; then
		echo -e "\e[32mOK\e[0m"
	else
		echo -e "\e[31mNão é um subgrafo\e[0m";
	fi
done
