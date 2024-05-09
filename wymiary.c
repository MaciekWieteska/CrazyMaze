#include <stdio.h>
#include "funkcje.h"

int kolumny(FILE *in){
int c;
int z = 0;
int wiersze = 0;
int kolumny = 0;
int pocz = 0;
//printf("Jezeli to widzisz to znaczy ze wszystko dziala");
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

return kolumny;
}


int wiersze(FILE *in){
int c;
int z = 0;
int wiersze = 0;
int kolumny = 0;
int pocz = 0;
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

return wiersze;
}
