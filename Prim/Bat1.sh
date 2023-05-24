#!/bin/bash

# Binários
prim=./prim.bin

echo "Testando algoritmo de Prim"
echo -e "\n"
for i in instances/*.mtx
do
	echo -e "\e[33mInstância $i\e[0m";
	val=$($prim -f $i);
	
	correto=$(grep $i gabarito_agm.txt | cut -d ' ' -f 2);
	[ $val -eq $correto ] && echo -e "Custo \e[32mOK\e[0m" || echo  -e "\e[31mCusto incorreto\e[0m";

	$prim -f $i -s | sed -e 's/ /\n/g' -e 's/,/ /g' -e 's/[()]//g' | ./agm $i
	if [ $? -eq 0 ]; then
		echo -e "\e[32mOK\e[0m"
	else
		echo -e "\e[31mNão é um subgrafo\e[0m";
	fi
	echo -e "\n";
done
