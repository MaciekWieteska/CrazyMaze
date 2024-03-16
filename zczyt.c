#include <stdio.h>

int zczyt(FILE *in){
int c;
int z = 0;
int l = 0;
int max = 0;
int pocz = 0;
printf("Jezeli to widzisz to znaczy ze wszystko dziala");
while((c=fgetc(in))!=EOF){
z++;
if(c == '\n'){
l++;
if(pocz > max) {
	max = pocz;
}
pocz = 0;
}else{
pocz++;
}
}
if (pocz > max) {
 max = pocz;
  }

printf("Tyle w labiryncie jest znakow: %d\n", z);
printf("Tyle jest wierszy: %d\n", l);
printf("Tyle jest kolumn: %d\n", max);
return 0;
}
