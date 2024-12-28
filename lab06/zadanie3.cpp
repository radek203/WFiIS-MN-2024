#include <iostream>
#include <ostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <gsl/gsl_linalg.h>
#define eps 1e-8
#define e exp(1.0)
using namespace std;

int main() {
    std::ifstream fileA;
    fileA.open("Ab.txt");

    double tempValue;
    int n = 0;
    char checkForNewLine;

    while (fileA >> tempValue) {
        ++n;
        if ((checkForNewLine = fileA.peek()) == '\n' || checkForNewLine == EOF) {
            break;
        }
    }
    n = n - 1;
    fileA.seekg(0, ios::beg);

    gsl_matrix *A = gsl_matrix_calloc(n, n);
    gsl_vector *b = gsl_vector_calloc(n);
    gsl_matrix *LU = gsl_matrix_calloc(n, n);
    gsl_permutation *p = gsl_permutation_calloc(n);
    gsl_vector *x = gsl_vector_alloc(n);
    double val;
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            fileA >> val;
            gsl_matrix_set(A, x, y, val);
        }
        fileA >> val;
        gsl_vector_set(b, x, val);
    }

    int s;

    gsl_linalg_LU_decomp(A, p, &s);

    gsl_linalg_LU_solve(A, p, b, x);

    printf("x = \n");
    gsl_vector_fprintf(stdout, x, "%g");

    std::ofstream fileX;
    fileX.open("x.txt");
    for (int i = 0; i < n; i++) {
        fileX << gsl_vector_get(x, i) << "\n";
    }

    fileX.close();
    fileA.close();

    gsl_permutation_free(p);
    gsl_vector_free(x);
    gsl_matrix_free(A);
    gsl_vector_free(b);
    gsl_matrix_free(LU);

    return 0;
}
