all:
	gcc -g -c main.c 
	gcc -g -c matriz_esparsa.c
	gcc -g -c vetor_esparso.c 
	gcc -o main main.o matriz_esparsa.o vetor_esparso.o
	./main
	del *.o
	del *.exe