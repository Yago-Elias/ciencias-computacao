#!/bin/bash

if [ -a a.out ]
	then
		rm a.out
		echo "~ a.out removido"
fi
echo
echo "~ compilando..."
gcc mouse.c main.c ../stack.c
echo "~ compilação completa"
echo "~ execusão em adamento..."
./a.out < labirinto.txt
echo "~ pronto."
echo
