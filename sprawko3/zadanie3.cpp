#include "../utilsGsl.h"

constexpr double eps = 1e-7;
constexpr double h = 1e-2;
constexpr int iterNum = 100000;

/*
 // Zadanie 3a
constexpr int n = 2;

double f0(double x[n]) {
    return 2 * pow(x[0], 2) + 3 * pow(x[1], 2) - 5;
}

double f1(double x[n]) {
    return pow(x[0], 3) - log(x[1]);
}
 */

/*
// Zadanie 3b
constexpr int n = 2;

double f0(double x[n]) {
	return 8 * pow(x[0], 3) + pow(x[1], 3) - 12 * x[0] * x[1];
}

double f1(double x[n]) {
	return cos(2*x[0]) - pow(x[1], 2) + 1;
}
 */

// Zadanie 3c
constexpr int n = 3;

double f0(double x[n]) {
    return (1.0 / 5.0) * pow(x[0] - 1, 2) + pow(x[1], 2) + (1.0 / 3.0) * pow(x[2], 2) - 6;
}

double f1(double x[n]) {
    return pow(x[0], 2) - 2.4 * x[0] + 2 * pow(x[1], 2) - x[2] + 0.06;
}

double f2(double x[n]) {
    return pow(x[2], 1.0 / 3.0) + 21 * sqrt(x[0]) + 20 * sqrt(x[1]) - 25;
}

/*
 // Zadanie 3d
constexpr int n = 3;

double f0(double x[n]) {
    return pow(x[0], 4) + pow(x[1], 2) + pow(x[2], 2) - 4;
}

double f1(double x[n]) {
    return pow(x[0], 2) + pow(x[1], 2) - 2 * tan(x[2]);
}

double f2(double x[n]) {
    return pow(x[0], 2) - pow(x[2], 2) + sin(x[0] * x[1] * x[2]) - 1.1;
}
 */

/*
// Zadanie 3e
constexpr int n = 3;

double f0(double x[n]) {
	return 3.2 * x[0] - cos(x[1] * x[2]) - 0.55;
}

double f1(double x[n]) {
	return pow(x[0], 2) - 80.45 * pow(x[1] + 0.095, 2) + sin(x[2]) + 1.07;
}

double f2(double x[n]) {
	return pow(2.71828182845904523536, -x[0] * x[1]) + 19.5 * x[2] + 30.5;
}
*/

int main() {
    gsl_matrix *a = gsl_matrix_calloc(n, n);
    gsl_vector *deltaX = gsl_vector_calloc(n);
    gsl_vector *b = gsl_vector_calloc(n);

    double (*f[n])(double x[n]) = {f0, f1, f2}; // To trzeba zmieniac

    double x[n] = {0.0, 1.25, 3.25}; // To tez trzeba zmieniac // 1.0, -1.0, 1.0

    std::cout << "Punkt startowy: ";
    printVector(x);

    double x_plus_h[n], x_minus_h[n];

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

        double x_copy[n];
        for (int i = 0; i < n; i++) {
            x_copy[i] = x[i];
            x[i] = x[i] + gsl_vector_get(deltaX, i);
        }

        // Sprawdzamy osiagnieta dokladnosc
        double difference = 0;
        double reference = 0;
        for (int i = 0; i < n; i++) {
            difference += std::abs(pow(x[i] - x_copy[i], 2));
            reference += std::abs(pow(x_copy[i], 2));
        }

        if (sqrt(difference) < eps * sqrt(reference)) {
            std::cout << "Osiagnelismy zadana dokladnosc po " << k << " iteracjach" << std::endl;
            break;
        }
    }

    printVector(x);

    for (int i = 0; i < n; i++) {
        std::cout << "f" << i << "(x) = " << f[i](x) << std::endl;
    }
}
