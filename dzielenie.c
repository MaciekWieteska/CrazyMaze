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
		
		for (int i = 1; i < aktw; ++i) {
            while ((a = fgetc(in)) != '\n' && a != EOF); // Przesuń do końca aktualnego wiersza
        }
		
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
				if(aktk -1 == kolumny)
				{
					break;
				}
			} 
			while((a = fgetc(in)) != '\n')
			{
				aktk++;
			} 
			fputc('\n', out);
			aktw++;
			aktk = (k-1)*ROZMIAR + 1;
			if(aktw == wiersze) // Problemem jest to, że brakuje 1 linii w ostatnim i ręcznie jest dodawana
			{
				fseek(in, aktk - 1 , SEEK_CUR);
				int pomk = aktk;
				while ((a = fgetc(in)) != EOF) //Pisanie kolejnych liter z pliku  działa git(dobrze bierze nowe litery)
				{	while(pomk <= k*ROZMIAR)
					{
						fputc(a, out);
						pomk++;
						break;
					}
					if(pomk -1 == kolumny)
					{
						break;
					}
				}
				break;
			}
		}
        fclose(out);	
		if((aktw == w*ROZMIAR + 1 && k != maxk) || aktw   == wiersze) // Przejscie o segment w prawo 
		{
			k++;
			aktw = (w-1)*ROZMIAR + 1;// + 1
			aktk = aktk + ROZMIAR;
		}
		else if(k == maxk) // Przejście w prawy niższy róg 
		{
			k = 1;
			aktk = 1;
			w++;
			aktw = (w-1)*ROZMIAR + 1; // + 1
		}
    }

    // Zwolnienie pamięci dla numer i nazwa poza pętlą
    free(nazwa);
}
