#include <stdio.h>
#include <stdlib.h>
#include "funkcje.h"

struct s {
    int File_Id;
    char ESC;
    short columns;
    short lines;
    short entryx;
    short entryy;
    short exitx;
    short exity;
    char reserved[12];
    int counter;
    int solution_offset;
    char separator;
    char wall;
    char path;
} __attribute__((packed));

struct slowo{
    char sep;
    char val;
    unsigned char amount;
}__attribute__((packed));

int odczyt(FILE *f, FILE *out, struct s *header) {
    int currX = 1;
    int currY = 1;

    if (fread(header, 40, 1, f) != 1) {
        return -1;
    }

    struct slowo* slowa = malloc(header->counter * 3);

    if(slowa == NULL)
        return -1;

    if (fread(slowa, 3, header->counter, f) != header->counter) {
        free(slowa);
        return -1;
    }

    for(int i = 0; i < header->counter; i++)
    {
        for (int y = 0; y < slowa[i].amount + 1; y++) {
            if (currX == header->entryx && currY == header->entryy) {
                fprintf(out, "P");
            } else if (currX == header->exitx && currY == header->exity) {
                fprintf(out, "K");
            } else {
                fprintf(out, "%c", slowa[i].val);
            }

            currX++;

            if (currX == header->columns+1) {
                fprintf(out, "\n");
                currX = 1;
                currY++;
            }
        }
    }

    free(slowa);
    return 0;
}