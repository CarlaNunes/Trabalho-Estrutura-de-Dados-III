############################# Makefile ##########################
all: programaTrab

programaTrab: manipularArquivo.o main.o 
        # O compilador faz a ligação entre os dois objetos
		gcc -o programaTrab manipularArquivo.o main.o
#-----> Distancia com o botão TAB ### e não com espaços

manipularArquivo.o: manipularArquivo.c
		gcc -o manipularArquivo.o -c manipularArquivo.c -W -Wall -ansi -pedantic

main.o: main.c manipularArquivo.h
		gcc -o main.o -c main.c -W -Wall -ansi -pedantic

clean:
		rm -rf *.o

mrproper: clean
		rm -rf programaTrab
