#include <stdio.h>
#include <iostream>
#include <gsl/gsl_linalg.h>

int main() {
    int n = 4;

    FILE *fp;
    if ((fp = fopen("dane.txt", "rt")) == NULL) {
        printf("\n*** (dane.txt) ***\n");
        return 1;
    }

    double val;

    gsl_matrix *a = gsl_matrix_calloc(n, n);
    gsl_vector *b = gsl_vector_calloc(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(fp, "%lf", &val);
            gsl_matrix_set(a, i, j, val);
        }
        fscanf(fp, "%lf", &val);
        gsl_vector_set(b, i, val);
    }

    fclose(fp);

    gsl_vector *x = gsl_vector_alloc(n);

    int s;

    gsl_permutation *p = gsl_permutation_alloc(n);

    gsl_linalg_LU_decomp(a, p, &s);

    gsl_linalg_LU_solve(a, p, b, x);

    printf("x = \n");
    gsl_vector_fprintf(stdout, x, "%g");

    gsl_permutation_free(p);
    gsl_vector_free(x);
    return 0;
}
