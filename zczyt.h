#ifndef ZCZYT_H
#define ZCZYT_H

#include <stdio.h>

int wiersze(FILE *in);
int kolumny(FILE *in);
void dzielenie(FILE *in, int wiersze, int kolumny);
char* nazwa(int w, int k);

#endif

