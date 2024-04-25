#include <stdio.h>
#include <stdlib.h>
#include "funkcje.h"




int ustal_kierunek_kon(FILE* in, int pozycja, int a, int kol)
{
	fseek(in, pozycja - kol, SEEK_SET); 
	a=fgetc(in);// góra
	if(a == 'U' || a == 'D' || a == 'R' || a == 'L')
	{
		return 'U'; 
	}
	fseek(in, pozycja + kol, SEEK_SET); // dół
	a=fgetc(in);
	if(a == 'U' || a == 'D' || a == 'R' || a == 'L')
	{
		return 'D'; 
	}
	fseek(in, pozycja + 1, SEEK_SET); // prawo
	a=fgetc(in);
	if(a == 'U' || a == 'D' || a == 'R' || a == 'L')
	{
		return 'R'; 
	}
	fseek(in, pozycja - 1 , SEEK_SET); // lewo
	a=fgetc(in);
	if(a == 'U' || a == 'D' || a == 'R' || a == 'L')
	{
		return 'L'; 
	}	
}


int ustal_kierunek_pocz(FILE* in, int pozycja, int a, int kol)
{
	fseek(in, pozycja - kol, SEEK_SET); // góra
	if((a = fgetc(in)) == ' ')
	{
		return 'D'; 
	}
	fseek(in, pozycja + kol, SEEK_SET); // dół
	if((a = fgetc(in)) == ' ')
	{
		return 'U'; 
	}
	fseek(in, pozycja + 1, SEEK_SET); // prawo
	if((a = fgetc(in)) == ' ')
	{
		return 'L'; 
	}
	fseek(in, pozycja - 1 , SEEK_SET); // lewo
	if((a = fgetc(in)) == ' ')
	{
		return 'R'; 
	}	
}


int graf2(FILE* in, FILE* out, int wiersze, int kolumny, FILE* wynik){ // główna funkcja
	int a; 
	int* kolejka = (int*)malloc(sizeof(int)*100000);
	int kol = kolumny + 1;
	int dodaj_kolejka = 0;
	int czytaj_kolejka = 0;
	char kierunek; 
	int pozycja = 0;
	int kroki_zgodne_z_kierunkiem = 0;
	
	
	// przepisanie labiryntu XD
	while((a = fgetc(in)) != EOF) // przepisuje labirynt
	{
		fputc(a, out);
	}
	
	rewind(out);
	rewind(in);
	
	while((a = fgetc(out)) != 'P')  // dojście do Początku P 
	{
		pozycja++;	
	}
	
	kierunek = ustal_kierunek_pocz(out, pozycja, a, kol); // wybranie odpowiedniego kierunku na początek
	
	while(1) // Znalezienie K doprowadzi do break 
	{
		fseek(out, pozycja - kol, SEEK_SET); // góra
		a = fgetc(out);
		if(a == 'K')
		{
			break; // jeżeli znaleziono k to pętla się kończy 
		}
		if(a == ' ')
		{
			kolejka[dodaj_kolejka] = pozycja - kol; // włożenie pozycji do kolejki 
			dodaj_kolejka++;
			fseek(out, pozycja - kol, SEEK_SET);
			kierunek = 'D'; 
		    fputc(kierunek, out);
		}
				
		fseek(out, pozycja + kol, SEEK_SET); // dół
		a = fgetc(out);
		if(a == 'K')
		{
			break;
		}
		if(a == ' ')
		{
			kolejka[dodaj_kolejka] = pozycja + kol;
			dodaj_kolejka++;
			fseek(out, pozycja + kol, SEEK_SET);
			kierunek = 'U'; 
			fputc(kierunek, out);
		}
				
		fseek(out, pozycja + 1, SEEK_SET); // prawo
		a = fgetc(out);
		if(a == 'K')
		{
			break;
		}
		if(a == ' ')
		{
			kolejka[dodaj_kolejka] = pozycja + 1;
			dodaj_kolejka++;
			fseek(out, pozycja + 1, SEEK_SET);
			kierunek = 'L'; 
			fputc(kierunek, out);
		}
				
		fseek(out, pozycja - 1, SEEK_SET); // lewo
		a = fgetc(out);
		if(a == 'K')
		{
			break;
		}
		if(a == ' ')
		{
			kolejka[dodaj_kolejka] = pozycja - 1;
			dodaj_kolejka++;
			fseek(out, pozycja - 1, SEEK_SET); 
			kierunek = 'R'; 
			fputc(kierunek, out);
		}
		pozycja = kolejka[czytaj_kolejka]; 
		czytaj_kolejka++; 
	}
	
	// odczytanie wyniku i wpisanie go do pliku
	pozycja = 0;
	rewind(out);
	while((a = fgetc(out)) != 'K')  // dojście do końca K 
	{
		pozycja++;
	}
	kierunek = ustal_kierunek_kon(out, pozycja, a, kol);
	
	if(kierunek == 'U')
	{
		fseek(out, pozycja - kol, SEEK_SET);
		pozycja = pozycja - kol;
		kroki_zgodne_z_kierunkiem++;
	}
	if(kierunek == 'D')
	{
		fseek(out, pozycja + kol, SEEK_SET);
		pozycja = pozycja + kol; 
		kroki_zgodne_z_kierunkiem++;
	}
	if(kierunek == 'R')
	{
		fseek(out, pozycja + 1, SEEK_SET);
		pozycja = pozycja + 1; 
		kroki_zgodne_z_kierunkiem++;
	}
	if(kierunek == 'L')
	{
		fseek(out, pozycja - 1, SEEK_SET);
		pozycja = pozycja - 1;
		kroki_zgodne_z_kierunkiem++;
	}
	
	while(1) 
	{
		a = fgetc(out); 
		if( a == 'U'){
			if(kierunek != 'U')
			{
					fprintf(wynik, "%c%d", kierunek, kroki_zgodne_z_kierunkiem);
					kroki_zgodne_z_kierunkiem = 1;
					kierunek = a;
			}
			else{
				kroki_zgodne_z_kierunkiem++;
			}
			pozycja = pozycja - kol; 
			fseek(out, pozycja, SEEK_SET);
		}
		if( a == 'D'){
			if(kierunek != 'D')
			{
					fprintf(wynik, "%c%d", kierunek, kroki_zgodne_z_kierunkiem);
					kroki_zgodne_z_kierunkiem = 1;
					kierunek = a;
			}
			else{
				kroki_zgodne_z_kierunkiem++;
			}
			pozycja = pozycja + kol; 
			fseek(out, pozycja, SEEK_SET);
		}
		if( a == 'R'){
			if(kierunek != 'R')
			{
					fprintf(wynik, "%c%d", kierunek, kroki_zgodne_z_kierunkiem);
					kroki_zgodne_z_kierunkiem = 1;
					kierunek = a;
			}
			else{
				kroki_zgodne_z_kierunkiem++;
			}
			pozycja = pozycja + 1; 
			fseek(out, pozycja, SEEK_SET);
		}
		if( a == 'L'){
			if(kierunek != 'L')
			{
					fprintf(wynik, "%c%d", kierunek, kroki_zgodne_z_kierunkiem);
					kroki_zgodne_z_kierunkiem = 1;
					kierunek = a;
			}
			else{
				kroki_zgodne_z_kierunkiem++;
			}
			pozycja = pozycja - 1; 
			fseek(out, pozycja, SEEK_SET);
		}
		if( a == 'P'){
			fprintf(wynik, "%c%d", kierunek, kroki_zgodne_z_kierunkiem);
			kroki_zgodne_z_kierunkiem = 1;
			kierunek = a;
			break;
		}
	}
	
	// robi moonwalk jak Majkel Dżekson   
	
	
	return 0;
}