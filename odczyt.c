#include <stdio.h>
#include <stdlib.h>

int odczyt(FILE *f, FILE *out) {
    char* buffer = malloc(40);

    int liczba_slow;

    fread(buffer, 40, 1, f);

    char* pointer = buffer;
    pointer += 29;

    liczba_slow = *(int*)pointer;

    unsigned char wartosc;
    char slowo;

    free(buffer);

    buffer = malloc(liczba_slow * 3);

    fread(buffer, liczba_slow * 3, 1, f);

    pointer = buffer;

    int counter = 0;

    FILE* out = fopen("nowy", "w");

    for(int i = 0; i < liczba_slow; i++)
    {
        pointer++;
        slowo = *pointer;
        pointer++;
        wartosc = *pointer;
        pointer++;

        for(int y = 0; y < wartosc+1; y++)
        {
            fprintf(out, "%c", slowo);
            counter++;
            if(counter == 513)
            {
                fprintf(out, "\n");
                counter = 0;
            }
        }
    }


    free(buffer);
    return 0;

}
