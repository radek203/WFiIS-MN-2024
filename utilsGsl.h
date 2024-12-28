#ifndef NUMERKI_UTILSGSL_H
#define NUMERKI_UTILSGSL_H
#include "utils.h"
#include <gsl/gsl_linalg.h>

void printMatrix(const gsl_matrix *matrix, int precision = 10) {

    std::cout << std::setprecision(precision);

    for (int i = 0; i < matrix->size1; i++) {
        for (int j = 0; j < matrix->size2; j++) {
            std::cout << gsl_matrix_get(matrix, i, j) << " ";
        }
        std::cout << std::endl;
    }
}

void printVector(const gsl_vector *vector, int precision = 10) {

    std::cout << std::setprecision(precision);

    for (int i = 0; i < vector->size; i++) {
        std::cout << gsl_vector_get(vector, i) << " ";
    }
    std::cout << std::endl;
}

template <size_t n>
void vectorGslToArray(const gsl_vector *vector, double (&a)[n]) {
    for (int i = 0; i < n; i++) {
        a[i] = gsl_vector_get(vector, i);
    }
}

template <size_t n>
void arrayToVectorGsl(const double (&a)[n], gsl_vector *vector) {
    for (int i = 0; i < n; i++) {
        gsl_vector_set(vector, i, a[i]);
    }
}

template <size_t n, size_t m>
void matrixGslToArray(const gsl_matrix *matrix, double (&a)[n][m]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[i][j] = gsl_matrix_get(matrix, i, j);
        }
    }
}

template <size_t n, size_t m>
void arrayToMatrixGsl(const double (&a)[n][m], gsl_matrix *matrix) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            gsl_matrix_set(matrix, i, j, a[i][j]);
        }
    }
}

#endif
