#!/bin/bash

# Binários
dijkstra=./dijkstra.bin

echo "Testando algoritmo de Dijkstra"
for i in instances/*.mtx
do
	echo -e "\e[33mInstância $i\e[0m";
	$dijkstra -f $i > temp;

	j=$(basename $i);
	diff -w temp ./sp/$j > /dev/null ;
	if [ $? -eq 0 ]; then
		echo -e "\e[32mOK\e[0m"
	else
		echo -e "\e[31mErro\e[0m";
	fi
	rm temp;

done
