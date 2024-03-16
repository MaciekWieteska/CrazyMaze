#include <stdio.h>
#include "zczyt.h"
int main(int argc, char*argv[]){
	FILE *in = argc > 1 ? fopen(argv[1], "r") : stdin;
if(in==NULL){
	printf("Blad, nie moge czytac z: %s", argv[0]);
	return -13;
}
zczyt(in);
	return 0;
}
