#ifndef _GAUSS_H
#define _GAUSS_H

#include "mat_io.h"

int findPivotRow(Matrix *mat, int col);
void swapRows(Matrix *mat, int row1, int row2);
int eliminate(Matrix *mat, Matrix *b);

#endif
