#include "../utilsGsl.h"

constexpr int n = 5; // O 1 mniej niz znamy punktow
constexpr int m = 2; // stopien wielomianu jaki chcemy

int main() {
    double x[n + 1] = {1.0, 2.0, 3.0, 5.5, 7.1, 8.2};
    double y[n + 1] = {-1, 0, 2, 4, -2, 5};

    // Tworzenie macierzy A i wektora b
    gsl_matrix *A = gsl_matrix_calloc(m + 1, m + 1);
    gsl_vector *b = gsl_vector_calloc(m + 1);

    // Wypełnianie macierzy A i wektora b
    for (int k = 0; k <= m; ++k) {
        for (int i = 0; i <= m; ++i) {
            double sum = 0.0;
            for (int j = 0; j <= n; ++j) {
                sum += pow(x[j], i + k);
            }
            gsl_matrix_set(A, i, k, sum);
        }

        double sum = 0.0;
        for (int j = 0; j <= n; ++j) {
            sum += y[j] * pow(x[j], k);
        }
        gsl_vector_set(b, k, sum);
    }

    // Rozwiazanie ukladu rownan
    gsl_vector *a = gsl_vector_calloc(m + 1);

    int s;

    gsl_permutation *p = gsl_permutation_calloc(m + 1);

    gsl_linalg_LU_decomp(A, p, &s);

    gsl_linalg_LU_solve(A, p, b, a);

    printVector(a);

    gsl_vector_free(a);
    gsl_vector_free(b);
    gsl_matrix_free(A);
    gsl_permutation_free(p);

    return 0;
}
