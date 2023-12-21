#include "gauss.h"
#include <math.h>

int findPivotRow(Matrix *mat, int col) {
    int n = mat->r;
    double **a = mat->data;
    int pivotRow = col;

    // Szukaj największej wartości bezwzględnej w kolumnie col
    for (int i = col + 1; i < n; i++) {
        if (fabs(a[i][col]) > fabs(a[pivotRow][col])) {
            pivotRow = i;
        }
    }

    return pivotRow;
}

void swapRows(Matrix *mat, int row1, int row2) {
    double **a = mat->data;
    int n = mat->r;

    // Zamień wiersze row1 i row2
    for (int i = 0; i < n; i++) {
        double temp = a[row1][i];
        a[row1][i] = a[row2][i];
        a[row2][i] = temp;
    }
}

int eliminate(Matrix *mat, Matrix *b) {
    int n = mat->r;
    double **a = mat->data;
    double **l = b->data;

    for (int k = 0; k < n - 1; k++) {
        // Wybierz element główny
        int pivotRow = findPivotRow(mat, k);

        // Zamień wiersze
        if (pivotRow != k) {
            swapRows(mat, k, pivotRow);
            swapRows(b, k, pivotRow);
        }

        // Eliminacja
        for (int w = k + 1; w < n; w++) {
            double wsp = a[w][k] / a[k][k];
            for (int i = k; i < n; i++) {
                a[w][i] -= a[k][i] * wsp;
            }
            l[w][0] -= l[k][0] * wsp;
        }
    }

    return 0;
}



