a.out: main.o wymiary.o grafSolver.o graf2.o
	gcc main.o wymiary.o grafSolver.o graf2.o -o a.out

main.o: main.c funkcje.h
	gcc -c main.c

wymiary.o: wymiary.c funkcje.h
	gcc -c wymiary.c
	
grafSolver.o: grafSolver.c funkcje.h
	gcc -c grafSolver.c

graf2.o: graf2.c funkcje.h 
	gcc -c graf2.c