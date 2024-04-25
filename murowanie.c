#include <stdio.h>
#include "funkcje.h"





int murowanie(FILE *in,FILE* out, int wiersze, int kolumny)
{
	int a; 
	int b; 
	int pozycja = 0;
	int sasiedzi = 0;
	int kol = kolumny + 1 ;
	int i = 0; 
	
	while((a = fgetc(in)) != EOF) // przepisuje labirynt
	{
		fputc(a, out);
	}
	
	rewind(out);
	
	
	// murowanie labiryntu
	while((b = fgetc(out)) != EOF)//dopóki nie dojdzie do końca pliku czyta kolejne znaki 
	{
		if( b == ' ')
		{
			fseek(out, pozycja - kol, SEEK_SET); // góra
			if((b = fgetc(out)) == 'X')
			{
				sasiedzi++;
			}
			fseek(out, pozycja + kol, SEEK_SET); // dół
			if((b = fgetc(out)) == 'X')
			{
				sasiedzi++;
			}
			fseek(out, pozycja + 1, SEEK_SET); // prawo
			if((b = fgetc(out)) == 'X')
			{
				sasiedzi++;
			}
			fseek(out, pozycja - 1 , SEEK_SET); // lewo
			if((b = fgetc(out)) == 'X')
			{
				sasiedzi++;
			}	
		}
		//printf("sasiedzi: %d\n", sasiedzi);
		if(sasiedzi == 3) // slepy zaułek 
		{
			
			//printf("%c ", b);
			fseek(out, pozycja, SEEK_SET);
			fputc('X', out);
			// wstawia znak w poszukiwane miejsce
			rewind(out); // powrot na start 
			//printf("od początku");
			pozycja = 0; 
			// i++;
			// printf("%d ", i);
		}
		else // idzie dalej do przodu 
		{
			pozycja ++;
			fseek(out, pozycja, SEEK_SET);
		}
	
		sasiedzi = 0;
	}
	return 0;
}