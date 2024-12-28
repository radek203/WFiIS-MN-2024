#include <stdio.h>
#include "/usr/include/gsl/gsl_math.h"
#include "/usr/include/gsl/gsl_linalg.h"

int main() {
    int n, i, j, k, s, pi;
    double val, sum, Lik, Ukj;
    FILE *fp;

    n = 8;
    gsl_matrix *A = gsl_matrix_calloc(n, n);
    gsl_matrix *LU = gsl_matrix_calloc(n, n);
    gsl_permutation *p = gsl_permutation_calloc(n);
    double x[n], q[n];

    if ((fp = fopen("A.txt", "rt")) == NULL) {
        printf("\n*** (A.txt) ***\n");
        return 1;
    }

    printf("\n*** Input matrix A ***\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            fscanf(fp, "%lf", &val);
            gsl_matrix_set(A, i, j, val);
            printf("%lf ", gsl_matrix_get(A, i, j));
        }
        printf("\n");
    }

    fclose(fp);

    gsl_linalg_LU_decomp(A, p, &s);

    printf("\n*** LU Decomposition of A ***\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) printf("%lf ", gsl_matrix_get(A, i, j));
        printf("\n");
    }

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            sum = 0;
            if (i <= j) {
                for (k = 0; k <= i - 1; k++) {
                    sum += gsl_matrix_get(A, i, k) * gsl_matrix_get(A, k, j);
                }
                sum += gsl_matrix_get(A, i, j);
            } else {
                for (k = 0; k <= j; k++) {
                    sum += gsl_matrix_get(A, i, k) * gsl_matrix_get(A, k, j);
                }
            }
            gsl_matrix_set(LU, i, j, sum);
        }

    printf("\n*** Result of multiplication L.U ***\n");
    for (i = 0; i < n; i++) {
        pi = gsl_permutation_get(p, i);
        q[pi] = i;
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) printf("%lf ", gsl_matrix_get(LU, q[i], j));
        printf("\n");
    }

    printf("\n*** P ***\n");
    for (i = 0; i < n; i++) printf("%d ", gsl_permutation_get(p, i));
    printf("\n");

    return 0;
}
