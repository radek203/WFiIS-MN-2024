#ifndef NUMERKI_UTILS_H
#define NUMERKI_UTILS_H
#include <iostream>
#include <ostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <functional>

int factorial(int n) {
    int fac = 1;
    for (int i = 1; i <= n; ++i) {
        fac *= i;
    }
    return fac;
}

void printValue(std::string xname, double x, int precision = 10) {
    std::cout << std::setprecision(precision);
    std::cout << xname << " = " << x << std::endl;
}

template <size_t n, size_t m>
void printMatrix(double (&matrix)[n][m], int precision = 10) {

    std::cout << std::setprecision(precision);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

template <size_t n>
void printVector(double (&vector)[n], int precision = 10) {

    std::cout << std::setprecision(precision);

    for (int i = 0; i < n; i++) {
        std::cout << vector[i] << " ";
    }
    std::cout << std::endl;
}

template <size_t n>
void matrixMultiply(double (&a)[n][n], double (&b)[n][n], double (&c)[n][n]) {
    for (int wiersz1 = 0; wiersz1 < n; wiersz1++) {
        for (int kolumna2 = 0; kolumna2 < n; kolumna2++) {
            for (int kolumna1 = 0; kolumna1 < n; kolumna1++) {
                c[wiersz1][kolumna2] += a[wiersz1][kolumna1] * b[kolumna1][kolumna2];
            }
        }
    }
}

template <size_t n>
void matrixVectorMultiply(double (&a)[n][n], double (&b)[n], double (&c)[n]) {
    for (int wiersz = 0; wiersz < n; wiersz++) {
        for (int kolumna = 0; kolumna < n; kolumna++) {
            c[wiersz] += a[wiersz][kolumna] * b[kolumna];
        }
    }
}

template <size_t n>
void loadMatrixFromFile(std::string name, double (&a)[n][n]) {
    std::ifstream fileA;
    fileA.open(name);

    if (!fileA) {
        std::cerr << "Failed to open file: " << name << std::endl;
        return;
    }

    for (int i = 0; i < n*n; i++) {
        fileA >> a[i/n][i%n];
    }

    fileA.close();
}

template <size_t n>
void loadMatrixAndVectorFromFile(std::string name, double (&a)[n][n], double (&b)[n]) {
    std::ifstream fileA;
    fileA.open(name);

    if (!fileA) {
        std::cerr << "Failed to open file: " << name << std::endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fileA >> a[i][j];
        }
        fileA >> b[i];
    }

    fileA.close();
}

#endif
