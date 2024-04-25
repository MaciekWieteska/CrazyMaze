#include <stdio.h>
#include <stdlib.h>
#include "funkcje.h"
#include <string.h>


int graf(FILE* in, FILE* out, int wiersze, int kolumny){

	int pozycja = 0;
	int kol = kolumny + 1;
	int a; // do chodzenia po in 
	char kierunek; 
	char kierunek_rozwidlenia; 
	int sasiedzi = 0;
	char skrety[] = "0000";
	FILE* lista = fopen("lista.txt", "w+");
	char bufor[13]; 
	char wzorzec[9]; 
	char* linia = NULL; 
	int liczba_rozwidlen = 0;
	FILE* aktualna_trasa = fopen("trasa", "w+");
	int ostatni; 
	int numer_rozwidlenia; 
	int liczba_krokow = 0; 
	int cofanie_BFS; 
	
	// lista wszystkich rozwidleń w pliku 
	while((a = fgetc(in)) != EOF){
		if( a == ' ')
		{
			fseek(in, pozycja - kol, SEEK_SET); // góra
			a = fgetc(in);
			if(a == ' ' || a == 'P' || a == 'k' )
			{
				skrety[0] = 'G'; 
				sasiedzi++; 
			}
			
			fseek(in, pozycja + kol, SEEK_SET); // dół
			a = fgetc(in);
			if(a == ' ' || a == 'P' || a == 'k' )
			{
				skrety[1] ='D'; 
				sasiedzi++; 
			}
			
			fseek(in, pozycja + 1, SEEK_SET); // prawo
			a = fgetc(in);
			if(a == ' ' || a == 'P' || a == 'k' )
			{
				skrety[2] = 'P'; 
				sasiedzi++; 
			}
			
			fseek(in, pozycja - 1, SEEK_SET); // lewo
			a = fgetc(in);
			if(a == ' ' || a == 'P' || a == 'k' )
			{
				skrety[3] = 'L'; 
				sasiedzi++; 
			}	
			
			if(sasiedzi == 3)
			{
				fprintf(lista, "%c%c%c%c.%d\n", skrety[0], skrety[1], skrety[2], skrety[3], pozycja); 
			}
			
			skrety[0] = '0';
			skrety[1] = '0';
			skrety[2] = '0';
			skrety[3] = '0';
			sasiedzi = 0;
			fseek(in, pozycja, SEEK_SET);
			liczba_rozwidlen++;
		}
		pozycja++; 
	}
	
	printf("%d", liczba_rozwidlen); 
	exit(0); 
	
	
	int* odwiedzone_rozwidlenia = (int*)malloc(sizeof(int)*((liczba_rozwidlen*8)/10));
	char* kierunek_odwiedzonego_rozwidlenia = (char*)malloc((liczba_rozwidlen*8)/10); 
	odwiedzone_rozwidlenia[0] = 0;
	
	rewind(lista); 
	while (fgets(bufor, 12, lista) != NULL) {
       // Sprawdź, czy fragment "330" jest częścią linii
       if (strstr(bufor, ".330\n") != NULL) {
           printf("Znaleziono linię zawierającą fragment \"330\": %s", bufor);
       }
    }

	rewind(lista); 
	rewind(in); 
	pozycja = 0;
	
	while((a = fgetc(in)) != 'P')
	{
		odwiedzone_rozwidlenia[0]++;	
	} // dobrze zlokalizowany START 
	
	// ustalenie kierunek na start
	pozycja = odwiedzone_rozwidlenia[0]; 	
	kierunek = ustal_kierunek_pocz(in, pozycja, a, kol); //
	kierunek_rozwidlenia = kierunek; 
	kierunek_odwiedzonego_rozwidlenia[0] = kierunek_rozwidlenia; 
	printf("%c %c",a, kierunek);
	rewind(in);
	
	
	//właściwe chodzenie
	while(1) // 
	{
		fseek(in, pozycja, SEEK_SET); 
		ostatni = 7; 
		otoczenie(in, out, pozycja, a, &sasiedzi, kol, &liczba_krokow, &kierunek);
		
		if(sasiedzi == 3) // rozwidlenie 
		{

			numer_rozwidlenia++; 
			odwiedzone_rozwidlenia[numer_rozwidlenia] = pozycja; 
			rewind(lista); 
			while (fgets(bufor, 12, lista) != NULL) {
				 sprintf(wzorzec, ".%d\n", pozycja);
				if (strstr(bufor, wzorzec) != NULL) {
					// znaleziono pasujące dane 
					if(bufor[0] == 'G') // idzie w góre 
					{
						kierunek_rozwidlenia = 'G'; 
						kierunek = 'G'; 
						kierunek_odwiedzonego_rozwidlenia[numer_rozwidlenia] = 'G'; 
						fseek(in, pozycja - kol, SEEK_SET); 
						pozycja = pozycja - kol; 
					}
					if(bufor[0] == 'D') // idzie w dół
					{
						kierunek_rozwidlenia = 'D'; 
						kierunek = 'D'; 
						kierunek_odwiedzonego_rozwidlenia[numer_rozwidlenia] = 'D'; 
						fseek(in, pozycja + kol, SEEK_SET); 
						pozycja = pozycja + kol; 
					}
					if(bufor[0] == 'P') // idzie w prawo
					{
						kierunek_rozwidlenia = 'P'; 
						kierunek = 'P'; 
						kierunek_odwiedzonego_rozwidlenia[numer_rozwidlenia] = 'P'; 
						fseek(in, pozycja + 1, SEEK_SET); 
						pozycja = pozycja + 1; 
					}
					if(bufor[0] == 'L') // idzie w lewo
					{
						kierunek_rozwidlenia = 'L'; 
						kierunek = 'L'; 
						kierunek_odwiedzonego_rozwidlenia[numer_rozwidlenia] = 'L'; 
						fseek(in, pozycja - 1, SEEK_SET); 
						pozycja = pozycja - 1; 
					}
					break; 
				}
			}
			
		}
		
		if(sasiedzi == 2) // idzie dalej Tu jest obsługa k --> jak dojdzie do k to zmienia na ostatnim rozwidleniu parametry 
		{
			chodzenie( in, out, a, wiersze, kol, &kierunek, &liczba_krokow, &pozycja);
		}
		
		if(sasiedzi == 1) // ślepy zaułek 
		{
			sasiedzi = 0; 
			// murowanie i wpisywanie nowego statusu do pliku lista 
			while(1){
				numer_rozwidlenia--; 
				fseek(in, odwiedzone_rozwidlenia[numer_rozwidlenia], SEEK_SET); // wraca do poprzedniego rozwidlenia
				pozycja = odwiedzone_rozwidlenia[numer_rozwidlenia];
				sasiedzi = otoczenie; 
				if(sasiedzi == 3)
				{
					// murowanie zgodnie z kierunkiem 
					if(kierunek_odwiedzonego_rozwidlenia[numer_rozwidlenia] == 'G')
					{
						fseek(in, pozycja - kol, SEEK_SET); 
						fputc('X', in); 
					}
					if(kierunek_odwiedzonego_rozwidlenia[numer_rozwidlenia] == 'D')
					{
						fseek(in, pozycja + kol, SEEK_SET); 
						fputc('X', in); 
					}
					if(kierunek_odwiedzonego_rozwidlenia[numer_rozwidlenia] == 'P')
					{
						fseek(in, pozycja + 1, SEEK_SET); 
						fputc('X', in); 
					}
					if(kierunek_odwiedzonego_rozwidlenia[numer_rozwidlenia] == 'L')
					{
						fseek(in, pozycja - 1, SEEK_SET); 
						fputc('X', in); 
					}
					break;
				}
			}
			
			
			pozycja = odwiedzone_rozwidlenia[0];
			fseek(in, pozycja, SEEK_SET); 
			
			while((a = fgetc(in)) != EOF){ // przeładowanie listy z rozwidleniami 
				if( a == ' ')
				{
					fseek(in, pozycja - kol, SEEK_SET); // góra
					a = fgetc(in);
					if(a == ' ' || a == 'P' || a == 'k' )
					{
						skrety[0] = 'G'; 
						sasiedzi++; 
					}
					
					fseek(in, pozycja + kol, SEEK_SET); // dół
					a = fgetc(in);
					if(a == ' ' || a == 'P' || a == 'k' )
					{
						skrety[1] ='D'; 
						sasiedzi++; 
					}
					
					fseek(in, pozycja + 1, SEEK_SET); // prawo
					a = fgetc(in);
					if(a == ' ' || a == 'P' || a == 'k' )
					{
						skrety[2] = 'P'; 
						sasiedzi++; 
					}
					
					fseek(in, pozycja - 1, SEEK_SET); // lewo
					a = fgetc(in);
					if(a == ' ' || a == 'P' || a == 'k' )
					{
						skrety[3] = 'L'; 
						sasiedzi++; 
					}	
					
					if(sasiedzi == 3)
					{
						fprintf(lista, "%c%c%c%c.%d\n", skrety[0], skrety[1], skrety[2], skrety[3], pozycja); 
					}
					
					skrety[0] = '0';
					skrety[1] = '0';
					skrety[2] = '0';
					skrety[3] = '0';
					sasiedzi = 0;
					fseek(in, pozycja, SEEK_SET);
					liczba_rozwidlen++;
				}
				pozycja++; 
			}
		}
		
		
		
		if( ostatni == 7)
		{
			break;
		}
	}



	fclose(lista);
	return 0;
}

void otoczenie(FILE* in, FILE* out, int pozycja, int a, int* sasiedzi, int kol, int* liczba_krokow, char* kierunek)
{
	sasiedzi = 0;
	fseek(in, pozycja - kol, SEEK_SET); // góra
	a = fgetc(in);
	if(a == ' ' || a == 'P' || a == 'k' )
	{
		*sasiedzi++; 
	}
			
	fseek(in, pozycja + kol, SEEK_SET); // dół
	a = fgetc(in);
	if(a == ' ' || a == 'P' || a == 'k' )
	{
		*sasiedzi++; 
	}
			
	fseek(in, pozycja + 1, SEEK_SET); // prawo
	a = fgetc(in);
	if(a == ' ' || a == 'P' || a == 'k' )
	{
		*sasiedzi++; 
	}
			
	fseek(in, pozycja - 1, SEEK_SET); // lewo
	a = fgetc(in);
	if(a == ' ' || a == 'P' || a == 'k' )
	{
		*sasiedzi++; 
	}
	
	
	// Bada czy obok jest K i jeżeli tak to zapisuje ostatni krok 
	fseek(in, pozycja - kol, SEEK_SET); // K jest na górze
	if((a = fgetc(in)) == 'K')
	{
		if( *kierunek == 'G') // jest zgodnie z kierunkiem 
		{
			*liczba_krokow++;
		}
		else // nie jest zgodne z kierunkiem 
		{
			fprintf(out, "%d%c", *liczba_krokow, *kierunek);
			*kierunek = 'G'; 
			*liczba_krokow = 1; 
		}
		fprintf(out, "%d%ck", *liczba_krokow, *kierunek);
		*liczba_krokow = 0;
		
	}
	fseek(in, pozycja + kol, SEEK_SET); // K jest na dole 
	if((a = fgetc(in)) == 'K')
	{
		if( *kierunek == 'D')
		{
			*liczba_krokow++;
		}
		else
		{
			fprintf(out, "%d%c", *liczba_krokow, *kierunek);
			*kierunek = 'D'; 
			*liczba_krokow = 1; 
		}
		fprintf(out, "%d%ck", *liczba_krokow, *kierunek);
		*liczba_krokow = 0;
	}
	fseek(in, pozycja + 1, SEEK_SET); // K jest w prawo
	if((a = fgetc(in)) == 'K')
	{
		if( *kierunek == 'P')
		{
			*liczba_krokow++;
		}
		else
		{
			fprintf(out, "%d%c", *liczba_krokow, *kierunek);
			*kierunek = 'P'; 
			*liczba_krokow = 1; 
		}
		fprintf(out, "%d%ck", *liczba_krokow, *kierunek);
		*liczba_krokow = 0;
	}
	fseek(in, pozycja - 1, SEEK_SET); // K jest w lewo
	if((a = fgetc(in)) == 'K')
	{
		if( *kierunek == 'L')
		{
			*liczba_krokow++;
		}
		else
		{
			fprintf(out, "%d%c", *liczba_krokow, *kierunek);
			*kierunek = 'L'; 
			*liczba_krokow = 1; 
		}
		fprintf(out, "%d%ck", *liczba_krokow, *kierunek);
		*liczba_krokow = 0;
	} 
	
}

int ustal_kierunek_pocz(FILE* in, int pozycja, int a, int kol)
{
	fseek(in, pozycja - kol, SEEK_SET); // góra
	if((a = fgetc(in)) == ' ')
	{
		return 'G'; 
	}
	fseek(in, pozycja + kol, SEEK_SET); // dół
	if((a = fgetc(in)) == ' ')
	{
		return 'D'; 
	}
	fseek(in, pozycja + 1, SEEK_SET); // prawo
	if((a = fgetc(in)) == ' ')
	{
			return 'P'; 
	}
	fseek(in, pozycja - 1 , SEEK_SET); // lewo
	if((a = fgetc(in)) == ' ')
	{
		return 'L'; 
	}	
}


void chodzenie(FILE* in, FILE* out, int a, int wiersze, int kol, char* kierunek, int* liczba_krokow, int* pozycja) // zwykłe chodzenie w strone kierunek 
{
	// Prosto dotychczasowym kierunkiem 
	fseek(in, *pozycja - kol, SEEK_SET); // góra
	if((a = fgetc(in)) == ' ' && *kierunek == 'G')
	{
		(*liczba_krokow)++;
	}
	
	fseek(in, *pozycja + kol, SEEK_SET); // dół
	if((a = fgetc(in)) == ' ' && *kierunek == 'D')
	{
		(*liczba_krokow)++;
	}
	
	fseek(in, *pozycja + 1, SEEK_SET); // prawo
	if((a = fgetc(in)) == ' ' && *kierunek == 'P')
	{
		(*liczba_krokow)++;
	}
	
	fseek(in, *pozycja - 1, SEEK_SET); // lewo
	if((a = fgetc(in)) == ' ' && *kierunek == 'L')
	{
		(*liczba_krokow)++;
	} 
	
	
	// Zakręt Zmiana kierunku - wypisuje do pliku informacje o kierunku 
	fseek(in, *pozycja - kol, SEEK_SET); // Zakret w góre
	if((a = fgetc(in)) == ' ' && *kierunek != 'G')
	{
		fprintf(out, "%d%c", *liczba_krokow, *kierunek);
		*kierunek = 'G'; 
		*liczba_krokow = 0;
	}
	
	fseek(in, *pozycja + kol, SEEK_SET); // Zakret w dół
	if((a = fgetc(in)) == ' ' && *kierunek != 'D')
	{
		fprintf(out, "%d%c", *liczba_krokow, *kierunek);
		*kierunek = 'D'; 
		*liczba_krokow = 0;
	}
	
	fseek(in, *pozycja + 1, SEEK_SET); // Zakręt w prawo
	if((a = fgetc(in)) == ' ' && *kierunek != 'P')
	{
		fprintf(out, "%d%c", *liczba_krokow, *kierunek);
		*kierunek = 'P'; 
		*liczba_krokow = 0;
	}
	
	fseek(in, *pozycja - 1, SEEK_SET); // Zakręt w lewo
	if((a = fgetc(in)) == ' ' && *kierunek != 'L')
	{
		fprintf(out, "%d%c", *liczba_krokow, *kierunek);
		*kierunek = 'L'; 
		*liczba_krokow = 0;
	} 
	
	
	// koniec badania otoczenia - teraz trzeba przenieść wskaźnik pliku in we właściwe zgodne z poruszaniem się 
	if(*kierunek == 'G') // przeniesienie do pozycji w górę
	{
		fseek(in, *pozycja - kol, SEEK_SET); 
		*pozycja = *pozycja - kol;
	}
	
	if(*kierunek == 'D') // przesunięcie do pozycji w dół 
	{
		fseek(in, *pozycja + kol, SEEK_SET); 
		*pozycja = *pozycja + kol;
	}
	
	if(*kierunek == 'P') // przesuniecie do pozycji w prawo
	{
		fseek(in, *pozycja + 1, SEEK_SET); 
		*pozycja = *pozycja + 1;
	}
	
	if(*kierunek == 'L') // Przesunięcie do pozycji w lewo 
	{
		fseek(in, *pozycja - 1, SEEK_SET); 
		*pozycja = *pozycja - 1;
	}
}