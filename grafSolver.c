#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int grafSolver(FILE *in, FILE *out) {
    int najmniejsza_suma = 400;
    int znaleziono_k = 0;

    char *linia = malloc(sizeof(char) * 500); 

    while (fgets(linia, 100, in) != NULL) {
        int dlugosc_linii = strlen(linia);
        if (linia[dlugosc_linii - 1] != '\n') { 
            int nowy_rozmiar = 2 * dlugosc_linii + 1;
            linia = realloc(linia, sizeof(char) * nowy_rozmiar); 
            if (linia == NULL) {
                fprintf(stderr, "Błąd alokacji pamięci.\n");
                return -1;
            }
        }

        if (strchr(linia, 'k') != NULL) {
            int suma = 0;
            for (int i = 0; linia[i] != '\0'; i++) {
                if (isdigit(linia[i])) {
                    suma += abs(linia[i] - '0');
                }
            }
            if (suma < najmniejsza_suma) {
                najmniejsza_suma = suma;
                znaleziono_k = 1;
            }
        }
    }

    free(linia); 

    if (znaleziono_k == 0) {
        fprintf(out, "Brak linii zawierających literę 'k'.\n");
        return -1;
    }

    fseek(in, 0, SEEK_SET);
    char sciezka[najmniejsza_suma];
    fgets(sciezka, sizeof(sciezka), in);
fprintf(out, "START\n");
    int dlugosc = strlen(sciezka);
    for (int i = 0; i < dlugosc; i += 2) {
        int liczba = abs(sciezka[i] - '0');
        char kierunek = sciezka[i + 1];
        switch (kierunek) {
            case 'U':
                fprintf(out, "FORWARD %d\n", liczba);
                break;
            case 'L':
                fprintf(out, "LEFT %d\n", liczba);
                break;
            case 'R':
                fprintf(out, "RIGHT %d\n", liczba);
                break;
            case 'D':
                fprintf(out, "DOWN %d\n", liczba);
                break;
        }
    }
fprintf(out,"STOP\n"); 
    return najmniejsza_suma;
}
