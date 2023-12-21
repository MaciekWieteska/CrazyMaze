#include "backsubst.h"

int backsubst(Matrix *x, Matrix *mat, Matrix *b) {
    if (mat->r != mat->c || mat->r != b->r || x->r != x->c || x->r != mat->r) {
        return 2; // Błąd nieprawidłowych rozmiarów macierzy
    }

    int n = mat->r;

    for (int i = n - 1; i >= 0; i--) {
        if (mat->data[i][i] == 0) {
            return 1; // Błąd dzielenia przez 0 (element na diagonali = 0)
        }

        x->data[i][0] = b->data[i][0] / mat->data[i][i];

        for (int j = i - 1; j >= 0; j--) {
            b->data[j][0] -= mat->data[j][i] * x->data[i][0];
        }
    }

    return 0; // Wsteczne podstawienie zakończone sukcesem
}

