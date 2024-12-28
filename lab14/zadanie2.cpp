#include "../utilsGsl.h"
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#define n 5

int main(void) {
    double A[n * n] = {};


    std::ifstream fileA;
    fileA.open("B.txt");

    if (!fileA) {
        std::cerr << "Failed to open file!" << std::endl;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fileA >> A[n * i + j];
        }
    }

    fileA.close();


    int i, j;

    gsl_vector *wart_wlasne = gsl_vector_alloc(n);
    gsl_matrix *wekt_wlasne = gsl_matrix_alloc(n, n);

    gsl_matrix_view A_mv = gsl_matrix_view_array(A, n, n);
    gsl_eigen_symmv_workspace *wsp = gsl_eigen_symmv_alloc(n);

    // Poprawne wywołanie funkcji gsl_eigen_symmv
    gsl_eigen_symmv(&A_mv.matrix, wart_wlasne, wekt_wlasne, wsp);
    gsl_eigen_symmv_free(wsp);
    gsl_eigen_symmv_sort(wart_wlasne, wekt_wlasne, GSL_EIGEN_SORT_ABS_ASC);

    for (i = 0; i < n; i++) {
        double wart_i = gsl_vector_get(wart_wlasne, i);
        gsl_vector_view wekt_i = gsl_matrix_column(wekt_wlasne, i);

        printf("wartość własna = %lf\n", wart_i);
        printf("wektor własny = \n");
        gsl_vector_fprintf(stdout, &wekt_i.vector, "%lf");
    }

    //Macierze A i B są podobne jeśli istnieje nieosobliwa macierz podobieństwa P, że:
    //Jeżeli macierze A i B są podobne to mają identyczne widmo wartości własnych

    gsl_vector_free(wart_wlasne);
    gsl_matrix_free(wekt_wlasne);

    return 0;
}
