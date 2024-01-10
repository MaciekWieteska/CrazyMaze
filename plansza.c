#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include "plansza.h"

void rysuj (int m, int n, int mrowka_m, int mrowka_n, int kierunek, int **t, FILE *out){

	for ( int j=1; j<=n; j++)
	{
		for ( int i=1; i<=m; i++)
        	{
			fprintf(out,"┌─┐");
	        }
		fprintf(out,"\n");
		for ( int i=1; i<=m; i++)
                {
			if (i == mrowka_m && j == mrowka_n)
			{
				if ( t[i][j]==0 )//bialy
				{
					if ( kierunek == 0 ) fprintf(out,"│△│");
					if ( kierunek == 1 ) fprintf(out,"│▷│");
					if ( kierunek == 2 ) fprintf(out,"│▽│");
					if ( kierunek == 3 ) fprintf(out,"│◁│");
				}
				else//czarny
                                {
                                        if ( kierunek == 0 ) fprintf(out,"│▲│");
                                        if ( kierunek == 1 ) fprintf(out,"│▶│");
                                        if ( kierunek == 2 ) fprintf(out,"│▼│");
                                        if ( kierunek == 3 ) fprintf(out,"│◀│");
                                }
			
			}
			else
			{
				if (t[i][j]==0) fprintf(out,"│ │");
				else fprintf(out,"│█│");
	
	 		}
		
                }
		fprintf(out,"\n");
		for ( int i=1; i<=m; i++)
                {
                        fprintf(out,"└─┘");

                }
		fprintf(out,"\n");
	}
	fprintf(out,"\n");
}

