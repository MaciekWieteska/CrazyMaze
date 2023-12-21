int piv_gauss_elim(Matrix *mat, Matrix *b) {
	    int n = mat->r;
	        double **a = mat->data;
		    double *bb = b->data[0];
		        for (int k = 0; k < n - 1; k++) {
				    int max = k;
					 for (int w = k + 1; w < n; w++)
			     if (a[w][k] > a[max][k])
			      max = w;
				   if (max != k) {
				    fprintf(stderr, "%d <-> %d\n", k, max);
				      double *tmp_row = a[k];
			      a[k] = a[max];
		        a[max] = tmp_row;
	          double bt = bb[max];
         bb[max] = bb[k];
      bb[k] = bt;
																		            }

			 for (int w = k + 1; w < n; w++) {
				double wsp = a[w][k] / a[k][k];
	  for (int i = k; i < n; i++)
	    a[w][i] -= a[k][i] * wsp;
   bb[w] -= bb[k] * wsp;
	}
}
return 0;
}
