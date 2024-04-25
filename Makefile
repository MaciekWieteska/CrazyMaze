a.out: main.o wymiary.o decoding.o grafSolver.o murowanie.o graf.o
	gcc main.o wymiary.o decoding.o grafSolver.o murowanie.o graf.o -o a.out

main.o: main.c funkcje.h
	gcc -c main.c

wymiary.o: wymiary.c funkcje.h
	gcc -c wymiary.c

decoding.o: decoding.c funkcje.h
	gcc -c decoding.c

grafSolver.o: grafSolver.c funkcje.h
	gcc -c grafSolver.c

murowanie.o: murowanie.c funkcje.h
	gcc -c murowanie.c
graf.o: graf.c funkcje.h 
	gcc -c graf.c