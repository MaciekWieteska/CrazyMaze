#include "gauss.h"

int eliminate(Matrix *mat, Matrix *b) {
	int n = mat->r;
		 double **a = mat->data;
		 double *l = b->data;

		  for (int k = 0; k < n - 1; k++) {
			   	 for (int w = k + 1; w < n; w++) {
					  if (a[k][k] == 0.0) {
						  	   return 1;
							    }
					      double wsp = a[w][k] / a[k][k];

					         for (int i = k; i < n; i++) {
							               a[w][i] -= a[k][i] * wsp;
								          }
						   l[w] -= l[k] * wsp;
						          	 }
				 					    }

		  			    return 0;
}


