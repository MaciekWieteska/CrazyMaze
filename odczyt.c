#include <stdio.h>
#include <stdlib.h>

int odczyt(FILE *f, FILE *out) {
    char* buffer = malloc(40);

    if (buffer == NULL) {
        return -1;
    }

    int liczba_slow;

    if (fread(buffer, 40, 1, f) != 1) {
        free(buffer);
        return -1;
    }

    char* pointer = buffer;
    pointer += 29;
    liczba_slow = *(int*)pointer;

    unsigned char wartosc;
    char slowo;

    free(buffer);
    buffer = malloc(liczba_slow * 3);

    if (buffer == NULL) {
        return -1;
    }

    if (fread(buffer, liczba_slow * 3, 1, f) != 1) {
        free(buffer);
        return -1;
    }

    pointer = buffer;


    int counter = 0;

    for (int i = 0; i < liczba_slow; i++) {
        pointer++;
        slowo = *pointer;
        pointer++;
        wartosc = *pointer;
        pointer++;

        for (int y = 0; y < wartosc+1; y++) {
            fprintf(out, "%c", slowo);
            counter++;
            if (counter == 513) {
                fprintf(out, "\n");
                counter = 0;
            }
        }
    }

    fclose(out);
    free(buffer);
    return 0;
}
