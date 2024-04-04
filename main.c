#include <stdio.h>
#include <stdlib.h>
#include "zczyt.h"
int kol;
int wier;
int main(int argc, char*argv[])
{
	FILE *in = argc > 1 ? fopen(argv[1], "r") : stdin;
	if(in==NULL)
	{
		fprintf(stderr,"Blad, nie moge czytac z: %s, %s", argv[0],argv[1]);
		return -13;
	}
FILE *out = argc > 2 ? fopen(argv[2], "w"): stdout;
if(in == NULL){
fprintf(out, "Nie moge pisac do: %s, %s", argv[0], argv[2]);
}
	kol = kolumny(in);
	rewind(in);
	wier = wiersze(in);
	rewind(in);
	dzielenie(in, wier, kol);
	rewind(in);
odczyt(in, out);
	fclose(in);
	return 0;
}
