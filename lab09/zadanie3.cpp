#include "../utilsGsl.h"

const int n = 3;

double f0(double x[n]) {
    return pow(x[0], 4) + pow(x[1], 2) + pow(x[2], 2) - 4;
}

double f1(double x[n]) {
    return pow(x[0], 2) + pow(x[1], 2) - 2 * tan(x[2]);
}

double f2(double x[n]) {
    return pow(x[0], 2) - pow(x[2], 2) + sin(x[0] * x[1] * x[2]) - 1.1;
}

int main() {
    gsl_matrix *a = gsl_matrix_calloc(n, n);
    gsl_vector *deltaX = gsl_vector_calloc(n);
    gsl_vector *b = gsl_vector_calloc(n);

    double (*f[n])(double x[n]) = {f0, f1, f2};

    double x[n] = {1.0, -1.0, 1.0};
    double x_plus_h[n], x_minus_h[n];

    double h = 0.01;

    int iterNum = 60;

    for (int k = 1; k <= iterNum; k++) {
        for (int i = 0; i < n; i++) {
            gsl_vector_set(b, i, -f[i](x));

            for (int j = 0; j < n; j++) {
                for (int r = 0; r < n; r++) {
                    if (r == j) {
                        x_plus_h[r] = x[r] + h;
                        x_minus_h[r] = x[r] - h;
                    } else {
                        x_plus_h[r] = x[r];
                        x_minus_h[r] = x[r];
                    }
                }

                gsl_matrix_set(a, i, j, (f[i](x_plus_h) - f[i](x_minus_h)) / (2 * h));
            }
        }

        int s;

        gsl_permutation *p = gsl_permutation_calloc(n);

        gsl_linalg_LU_decomp(a, p, &s);

        gsl_linalg_LU_solve(a, p, b, deltaX);

        for (int i = 0; i < n; i++) {
            x[i] = x[i] + gsl_vector_get(deltaX, i);
        }
    }

    printVector(x);

    for (int i = 0; i < n; i++) {
        std::cout << "f" << i << "(x) = " << f[i](x) << std::endl;
    }
}
