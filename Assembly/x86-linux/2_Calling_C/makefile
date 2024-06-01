public:
	nasm -f elf64 main.asm -o main.o
	gcc -c lib.c -o lib.o
	gcc -nostartfiles -no-pie main.o lib.o -o main -lc