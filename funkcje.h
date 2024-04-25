#ifndef ZCZYT_H
#define ZCZYT_H


int wiersze(FILE *in);
int kolumny(FILE *in);
//odczyt(FILE *f, FILE *out, struct s *header)
int graf(FILE* in, FILE* out, int wiersze, int kolumny);
int grafSolver(FILE *in, FILE *out);
int murowanie(FILE *in, FILE *out, int wiersze, int kolumny);


// tu mamy pomocnicze
int ustal_kierunek_pocz(FILE* in, int pozycja, int a, int kol);
void otoczenie(FILE* in, FILE* out, int pozycja, int a, int* sasiedzi, int kol, int* liczba_krokow, char* kierunek);
//void chodzenie(FILE* in, FILE* out, int a, int wiersze, int kol, char* kierunek, int* liczba_krokow, int* pozycja)

#endif

