#include "../utilsGsl.h"

constexpr int n = 4;

// Odwracanie macierzy i wymnozenie zeby uzyskac jednostkowa
int main() {
    double A[n][n] = {};
    double A_COPY[n][n] = {};

    loadMatrixFromFile("A.txt", A);
    loadMatrixFromFile("A.txt", A_COPY);

    printMatrix(A);

    gsl_matrix *MAT = gsl_matrix_calloc(n, n);

    arrayToMatrixGsl(A, MAT);

    gsl_vector *x = gsl_vector_calloc(n);

    int s;

    gsl_permutation *p = gsl_permutation_calloc(n);

    gsl_linalg_LU_decomp(MAT, p, &s);

    gsl_matrix *ODW = gsl_matrix_calloc(n, n);

    for (int i = 0; i < n; i++) {
        gsl_vector *y = gsl_vector_calloc(n);

        gsl_vector_set(y, i, 1);

        gsl_linalg_LU_solve(MAT, p, y, x);

        for (int j = 0; j < n; j++) {
            gsl_matrix_set(ODW, j, i, gsl_vector_get(x, j));
        }
    }

    double ODWR[n][n] = {};
    matrixGslToArray(ODW, ODWR);

    double JEDN[n][n] = {};
    matrixMultiply(ODWR, A, JEDN);

    printMatrix(JEDN);


    return 0;
}
