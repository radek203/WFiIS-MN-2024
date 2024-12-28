#include "../utilsGsl.h"

//O 1 mniej niz znamy punktow
constexpr int n = 6;

double fun(double x) {
    return 2 + 3 * x - 3.2 * pow(x, 2) + 7.5 * pow(x, 3) - 16 * pow(x, 4) + 0.1 * pow(x, 5) - 17.2 * pow(x, 6);
}

int main() {
    gsl_vector *a = gsl_vector_calloc(n + 1);
    gsl_vector *y = gsl_vector_calloc(n + 1);

    gsl_matrix *wsp = gsl_matrix_calloc(n + 1, n + 1);

    double x[n + 1] = {-2, 0, 1, 3, 4, 7, 9};

    for (int i = 0; i < n + 1; i++) {
        // Normalnie mielibysmy y podane (a nie mielibysmy funkcji), ale tutaj je obliczamy (na potrzeby nauki) zeby potem je odtworzyc
        gsl_vector_set(y, i, fun(x[i]));

        for (int j = 0; j < n + 1; j++) {
            gsl_matrix_set(wsp, i, j, pow(x[i], j));
        }
    }

    int s;

    gsl_permutation *p = gsl_permutation_calloc(n + 1);

    gsl_linalg_LU_decomp(wsp, p, &s);

    gsl_linalg_LU_solve(wsp, p, y, a);

    printVector(a);

    gsl_vector_free(a);
    gsl_vector_free(y);
    gsl_matrix_free(wsp);
    gsl_permutation_free(p);

    return 0;
}
