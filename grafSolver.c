#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int grafSolver(FILE *in, FILE *out) {
	fprintf(out, "START\n"); 
    char sciezka[400000]; 
    fgets(sciezka, sizeof(sciezka), in);

    int dlugosc = strlen(sciezka);
    int i = dlugosc - 1;
    while (i >= 0) {
        if (isdigit(sciezka[i])) {
            int j = i - 1;
            while (j >= 0 && isdigit(sciezka[j])) {
                j--;
            }
            int liczba_krokow = atoi(sciezka + j + 1);
            char kierunek = sciezka[j];
            switch (kierunek) {
                case 'U':
                    fprintf(out, "UPPER %d\n", liczba_krokow);
                    break;
                case 'L':
                    fprintf(out, "LEFT %d\n", liczba_krokow);
                    break;
                case 'R':
                    fprintf(out, "RIGHT %d\n", liczba_krokow);
                    break;
                case 'D':
                    fprintf(out, "DOWN %d\n", liczba_krokow);
                    break;
            }
            i = j - 1;
        } else {
            i--;
        }
    }

    fprintf(out, "STOP\n"); 
    return 0;
}
