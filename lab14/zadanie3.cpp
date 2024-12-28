#include "../utilsGsl.h"
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#define n 5

int main(void) {
    double A[n * n] = {2, 1, 5, 3, 4, 1, 0, 7, 2, 5, 5, 7, 1, 3, 0, 3, 2, 3, 2, -1, 4, 5, 0, -1, 8};
    double A_COPY[n * n] = {2, 1, 5, 3, 4, 1, 0, 7, 2, 5, 5, 7, 1, 3, 0, 3, 2, 3, 2, -1, 4, 5, 0, -1, 8};

    int i, j;

    gsl_vector *wart_wlasne = gsl_vector_alloc(n);
    gsl_matrix *wekt_wlasne = gsl_matrix_alloc(n, n);

    gsl_matrix_view A_mv = gsl_matrix_view_array(A, n, n);
    gsl_eigen_symmv_workspace *wsp = gsl_eigen_symmv_alloc(n);

    // Poprawne wywołanie funkcji gsl_eigen_symmv
    gsl_eigen_symmv(&A_mv.matrix, wart_wlasne, wekt_wlasne, wsp);
    gsl_eigen_symmv_free(wsp);
    gsl_eigen_symmv_sort(wart_wlasne, wekt_wlasne, GSL_EIGEN_SORT_ABS_ASC);


    gsl_matrix *P = gsl_matrix_calloc(n, n);
    gsl_matrix *P_COPY = gsl_matrix_calloc(n, n);

    for (i = 0; i < n; i++) {
        double wart_i = gsl_vector_get(wart_wlasne, i);
        gsl_vector_view wekt_i = gsl_matrix_column(wekt_wlasne, i);

        printf("wartość własna = %lf\n", wart_i);
        printf("wektor własny = \n");
        gsl_vector_fprintf(stdout, &wekt_i.vector, "%lf");

        for (int j = 0; j < n; j++) {
            gsl_matrix_set(P, j, i, gsl_vector_get(&wekt_i.vector, j));
            gsl_matrix_set(P_COPY, j, i, gsl_vector_get(&wekt_i.vector, j));
        }
    }

    std::cout << "P" << std::endl;
    printMatrix(P);


    gsl_vector *x = gsl_vector_calloc(n);

    int s;

    gsl_permutation *p = gsl_permutation_calloc(n);

    gsl_linalg_LU_decomp(P, p, &s);

    gsl_matrix *ODW = gsl_matrix_calloc(n, n);

    for (int i = 0; i < n; i++) {
        gsl_vector *y = gsl_vector_calloc(n);

        gsl_vector_set(y, i, 1);

        gsl_linalg_LU_solve(P, p, y, x);

        for (int j = 0; j < n; j++) {
            gsl_matrix_set(ODW, j, i, gsl_vector_get(x, j));
        }
    }


    std::cout << "P^-1" << std::endl;
    printMatrix(ODW);


    double C[n][n] = {};
    for (int wiersz1 = 0; wiersz1 < n; wiersz1++) {
        for (int kolumna2 = 0; kolumna2 < n; kolumna2++) {
            for (int kolumna1 = 0; kolumna1 < n; kolumna1++) {
                C[wiersz1][kolumna2] += gsl_matrix_get(ODW, wiersz1, kolumna1) * A_COPY[kolumna1 * n + kolumna2];
            }
        }
    }

    std::cout << "P^-1A" << std::endl;
    printMatrix(C);


    double D[n][n] = {};
    for (int wiersz1 = 0; wiersz1 < n; wiersz1++) {
        for (int kolumna2 = 0; kolumna2 < n; kolumna2++) {
            for (int kolumna1 = 0; kolumna1 < n; kolumna1++) {
                D[wiersz1][kolumna2] += C[wiersz1][kolumna1] * gsl_matrix_get(P_COPY, kolumna1, kolumna2);
            }
        }
    }


    std::cout << "P^-1AP" << std::endl;
    printMatrix(D);


    //Macierze A i B są podobne jeśli istnieje nieosobliwa macierz podobieństwa P, że:
    //Jeżeli macierze A i B są podobne to mają identyczne widmo wartości własnych

    gsl_vector_free(wart_wlasne);
    gsl_matrix_free(wekt_wlasne);

    return 0;
}
