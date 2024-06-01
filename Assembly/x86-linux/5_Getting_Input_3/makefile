public:
	nasm -f elf64 main.asm -o main.o
	gcc -c -o lib.o lib.c
	gcc -nostartfiles -no-pie -o main main.o lib.o