#include <stdio.h>

int kolumny(FILE *in){
int c;
int z = 0;
int wiersze = 0;
int kolumny = 0;
int pocz = 0;
printf("Jezeli to widzisz to znaczy ze wszystko dziala");
while((c=fgetc(in))!=EOF){
z++;
if(c == '\n'){
wiersze++;
if(pocz > kolumny) {
	kolumny = pocz;
}
pocz = 0;
}else{
pocz++;
}
}
if (pocz > kolumny) {
 kolumny = pocz;
  }

//printf("Tyle w labiryncie jest znakow: %d\n", z);
printf("Tyle jest kolumn: %d\n", kolumny);
return kolumny;
}


int wiersze(FILE *in){
int c;
int z = 0;
int wiersze = 0;
int kolumny = 0;
int pocz = 0;
printf("Jezeli to widzisz to znaczy ze wszystko dziala");
while((c=fgetc(in))!=EOF){
z++;
if(c == '\n'){
wiersze++;
if(pocz > kolumny) {
	kolumny = pocz;
}
pocz = 0;
}else{
pocz++;
}
}
if (pocz > kolumny) {
 kolumny = pocz;
  }

//printf("Tyle w labiryncie jest znakow: %d\n", z);
printf("Tyle jest wierszy: %d\n", wiersze);
return wiersze;
}
