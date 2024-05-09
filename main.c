#include <stdio.h>
#include <stdlib.h>
#include "funkcje.h"
#include <unistd.h>  
#include <string.h>

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

int kol;
int wier;
int opt;
FILE *in;





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








int main(int argc, char* argv[]) {
    struct s header;
	char* filename;

	if(argc == 1)
	{
		printf("Podano niewłaściwe dane wejściowe. Aby poznać działanie programu wywołaj go z argumentem -h\n");
        return 0;
	}
    while ((opt = getopt(argc, argv, "hl:")) != -1) {
        switch (opt) {
            case 'h': 
                printf("Witaj w programie rozwiązującym labirynt./nDziała on według poniższego wzoru wywołania:\n");
                printf("a.out -l 'nazwa pliku z labiryntem'\n");
                return 0;
                
            case 'l':
                if (optarg != NULL) {
                    filename = optarg; // Przypisz nazwę pliku z argumentu
                    break;
                } else {
                    printf("Nie podano argumentu wywołania\n");
                    return 1;
                }
			case '?': 
				printf("Podano niewłaściwe dane wejściowe. Aby poznać działanie programu wywołaj go z argumentem -h\n");
                return 0;
        }
    }

	
    if (strstr(filename, ".bin") != NULL) {
        in = fopen(filename, "rb");
		FILE* encr = fopen("maze_decoded.txt", "w+");
		odczyt(in, encr, &header);
		fclose(in);
		rewind(encr);
		kol = kolumny(encr);
		rewind(encr);
		wier = wiersze(encr);
		rewind(encr);
		

		FILE* graf_plik = fopen("graf.txt", "w+");
		FILE* wynik_t = fopen("wynik_temp.txt", "w+");
		graf2(encr, graf_plik, wier, kol, wynik_t);
		FILE* wynik = fopen("wynik.txt", "w+");
		fclose(encr);
		rewind(wynik_t);
		grafSolver(wynik_t, wynik);
		fclose(graf_plik);
		fclose(wynik_t);
		fclose(wynik);
		remove("maze_decoded.txt");
		remove("graf.txt"); 
		remove("wynik_temp.txt");
    } 
	else {
        in = fopen(filename, "r");
		kol = kolumny(in);
		rewind(in);
		wier = wiersze(in);
		rewind(in);
		
		FILE* graf_plik = fopen("graf.txt", "w+");
		FILE* wynik_t = fopen("wynik_temp.txt", "w+");
		graf2(in, graf_plik, wier, kol, wynik_t);
		fclose(in);
		FILE* wynik = fopen("wynik.txt", "w+");
		rewind(wynik_t);
		grafSolver(wynik_t, wynik);
		fclose(graf_plik);
		fclose(wynik_t);
		fclose(wynik);
		remove("graf.txt"); 
		remove("wynik_temp.txt");
    }

	
	
	return 0;
}
