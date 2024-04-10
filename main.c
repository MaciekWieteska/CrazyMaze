#include <stdio.h>
#include <stdlib.h>
#include "funkcje.h"
#include <unistd.h>  

int kol;
int wier;
int opt;
FILE *in;
char labirynt[513][513];
int main(int argc, char*argv[])
{
	
	while((opt = getopt(argc, argv, "w:n:hl:")) != -1)
	{
		switch(opt)
		{
			case 'h': //Pomoc
			printf("Witaj w programie rozwiązującym labirynt./nDziała on według poniższego wzoru wywołania:\n");
			printf("a.out -l 'nazwa pliku z labiryntem' -w / a.out -l 'nazwa pliku z labiryntem' -n gdzie:\n-w znajduje wszystkie rozwiązania labiryntu\n-n znajduje najkrótsze rozwiązanie labiryntu.\n-l zawiera nazwe pliku z labiryntem\n");
			return 0;
			
			case 'l': // nazwa pliku wejsciowego
			if(optarg != NULL)
			{
				in = fopen(optarg, "r");
				if(in==NULL)
				{
					fprintf(stderr,"Blad, nie moge czytac z: %s, %s", argv[0],optarg);
					return -13;
				}
				break;
			}
			else
			{
				printf("Nie podano argumentu wywołania\n");
				return 1;
			}
			
			case 'w': // wszystkie trasy
			//
			//Troche kodu
			//
			return 0;
			
			case 'n': // najkrótsza trasa 
			//
			//kod
			//
			return 0;
		}
	}
	
	if(fgetc(in) != 'X')
	{
		rewind(in);
		FILE* encr = fopen("maze_decoded.txt", "w+");
		odczyt(in, encr);
		fclose(in);
		
		rewind(encr);
		kol = kolumny(encr);
		rewind(encr);
		wier = wiersze(encr);
		rewind(encr);
murowanie(encr,wier, kol);
		//dzielenie(encr, wier, kol);
		//rewind(encr);
	
	
		fclose(encr);
	}
	else
	{
		kol = kolumny(in);
		rewind(in);
		wier = wiersze(in);
		rewind(in);
murowanie(in,wier, kol);
		//dzielenie(in, wier, kol);
		//rewind(in);
		
		fclose(in);
	}
	return 0;
}
