#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ROZMIAR 20

void dzielenie(FILE* in, int wiersze, int kolumny) 
{
    int a;
    int w = 1;
    int k = 1;
    int aktw = 1;
    int aktk = 1;
	int pis_start;
    int maxw = wiersze / ROZMIAR + 1;
    int maxk = kolumny / ROZMIAR + 1;
    char* nazwa = (char*)malloc(sizeof(char) * 50);

    while (w <= maxw && k <= maxk)
	{
        FILE* out;
        // Tworzenie nowej nazwy pliku
        sprintf(nazwa, "temp_W%dK%d.txt", w, k);
        
        out = fopen(nazwa, "w");
		rewind(in); // Zaczyna czytać plik od początku
		//Przewiniece do dobrego miejsca w pliku 
					
						printf("aktk %d aktw %d k %d w %d\n", aktk, aktw, k, w);
		//int i = 0;//fseek(in, (aktw - 1) * kolumny, SEEK_SET); // Przesunięcie do dobrej pozycji startowej(Wiersze)
		
		//fseek(in, (aktw-1)*kolumny, SEEK_CUR);
		
		while(aktw >= (w-1)*ROZMIAR && aktw <= w*ROZMIAR) // robienie segmentów(i wierszy)
		{
			fseek(in, aktk - 1 , SEEK_CUR);
			while(aktk >= (k-1)*ROZMIAR && aktk <= k*ROZMIAR) //Pisanie linijek 
			{
				while ((a = fgetc(in)) != EOF) //Pisanie kolejnych liter z pliku  działa git(dobrze bierze nowe litery)
				{	
					fputc(a, out);
					aktk++;
					break; // po wpisaniu litery wychodzi z pętli i patrzy co sie stalo 
				}
				if(aktk == kolumny)
				{
					break;
				}
				//printf("Petla %d %d\n", aktk, k); // Tu jestem udkniety
				// if((a = fgetc(in)) == EOF)
				// {
					// printf("zjebales\n");
				// }
			} 
			while((a = fgetc(in)) != '\n')
			{
				aktk++;
			} 
			fputc('\n', out);
			aktw++;
			aktk = (k-1)*ROZMIAR + 1;
			printf("aktw to %d\n", aktw);
			if(aktw == wiersze)
			{
				break;
			}
		}
        fclose(out);	
		if((aktw == w*ROZMIAR + 1 && k != maxk) || aktw == wiersze) // Przejscie o segment w prawo 
		{
			k++;
			aktw = (w-1)*ROZMIAR + 1;
			aktk = aktk + ROZMIAR;
		}
		else if(k == maxk) // Przejście w prawy niższy róg 
		{
			k = 1;
			aktk = 1;
			w++;
			aktw = (w-1)*ROZMIAR + 1;
					printf("JEST EZ\n");
		}
    }

    // Zwolnienie pamięci dla numer i nazwa poza pętlą
    free(nazwa);
}
