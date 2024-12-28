#include "../utilsGsl.h"

const int n = 2;
const double h = 0.0001;

double f1(double x, double y) {
    return 8 * pow(x, 3) + pow(y, 3) - 12 * x * y;
}

double f2(double x, double y) {
    return cos(2 * x) - pow(y, 2) + 1;
}

//Pochodna ilorazem roznicowym
double f1x_num(double x, double y) {
    return (f1(x + h, y) - f1(x - h, y)) / (2 * h);
}

double f1y_num(double x, double y) {
    return (f1(x, y + h) - f1(x, y - h)) / (2 * h);
}

double f2x_num(double x, double y) {
    return (f2(x + h, y) - f2(x - h, y)) / (2 * h);
}

double f2y_num(double x, double y) {
    return (f2(x, y + h) - f2(x, y - h)) / (2 * h);
}

int main() {
    gsl_matrix *a = gsl_matrix_calloc(n, n);
    gsl_vector *deltaX = gsl_vector_calloc(n);
    gsl_vector *b = gsl_vector_calloc(n);

    double x[n] = {1.0, 0.8};

    int iterNum = 1000;

    for (int k = 1; k <= iterNum; k++) {
        gsl_matrix_set(a, 0, 0, f1x_num(x[0], x[1]));
        gsl_matrix_set(a, 0, 1, f1y_num(x[0], x[1]));

        gsl_matrix_set(a, 1, 0, f2x_num(x[0], x[1]));
        gsl_matrix_set(a, 1, 1, f2y_num(x[0], x[1]));

        gsl_vector_set(b, 0, -f1(x[0], x[1]));
        gsl_vector_set(b, 1, -f2(x[0], x[1]));

        int s;

        gsl_permutation *p = gsl_permutation_calloc(n);

        gsl_linalg_LU_decomp(a, p, &s);

        gsl_linalg_LU_solve(a, p, b, deltaX);

        for (int i = 0; i < n; i++) {
            x[i] = x[i] + gsl_vector_get(deltaX, i);
        }
    }

    printVector(x);

    return 0;
}
