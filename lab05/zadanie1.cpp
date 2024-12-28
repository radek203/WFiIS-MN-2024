#include <cstdio>
#include "gsl/gsl_linalg.h"

int main() {
    int n, i, j, k, s;
    double sum, val, lik, ukj;
    FILE *fp;
    n = 8;
    gsl_matrix *A = gsl_matrix_calloc(n, n);
    gsl_matrix *LU = gsl_matrix_calloc(n, n);
    gsl_permutation *p = gsl_permutation_calloc(n);
    double x[n], q[n];

    //Wczytywanie, rozkład i wypisanie rozkładu:
    if ((fp = fopen("A.txt", "rt")) == nullptr) {
        printf("\n*** (A.txt) ***\n");
        return 1;
    }

    printf("\n*** Macierz A ***\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            fscanf(fp, "%lf", &val);
            gsl_matrix_set(A, i, j, val);
            printf("%.4lf ", gsl_matrix_get(A, i, j));
        }
        printf("\n");
    }

    fclose(fp);

    gsl_linalg_LU_decomp(A, p, &s);

    printf("\n*** Rozkład LU macierzy A ***\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) printf("%.4lf ", gsl_matrix_get(A, i, j));
        printf("\n");
    }

    gsl_matrix *A1 = gsl_matrix_calloc(n, n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            sum = 0;
            lik = 0;
            ukj = 0;
            for (k = 0; k < n; k++) {
                if (k < i) {
                    lik = gsl_matrix_get(A, i, k);
                } else if (k == i) {
                    lik = 1;
                } else {
                    lik = 0;
                }
                if (k > j) {
                    ukj = 0;
                } else {
                    ukj = gsl_matrix_get(A, k, j);
                }
                sum += lik * ukj;
            }
            gsl_matrix_set(A1, i, j, sum);
        }
    }

    printf("\n*** Macierz A1 ***\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%.4lf ", gsl_matrix_get(A1, i, j));
        }
        printf("\n");
    }


    return 0;
}
