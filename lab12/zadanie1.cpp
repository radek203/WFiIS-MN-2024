#include "../utilsGsl.h"

//O 1 mniej niz znamy punktow
constexpr int n = 6;

double fun(double x) {
    return sin(x);
}

int main() {
    gsl_vector *a = gsl_vector_calloc(n + 1);
    gsl_vector *y = gsl_vector_calloc(n + 1);

    gsl_matrix *wsp = gsl_matrix_calloc(n + 1, n + 1);

    double x[n + 1];
    for (int i = 0; i < n + 1; i++) {
        // Optymalne polozenie z wielomianow Czebywszewa
        x[i] = cos(((2 * i + 1.0) / (2 * n + 2.0)) * M_PI);
    }

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

    double xw = -1;
    double dx = 0.05;

    while (xw <= 1 + dx) {
        double war = fun(xw);

        double w_ = 0;
        for (int i = 0; i < n + 1; i++) {
            w_ += gsl_vector_get(a, i) * pow(xw, i);
        }
        double roznica = std::abs(war - w_);

        // Dla tego przykladu ograniczenie od gory n+1 pochodna wyszedl cos(x) lub sin(x) co daje max wartosc 1
        double ob = 1.0 / (factorial(n + 1) * pow(2, n));

        std::cout << "x = " << xw << "\tf(x) = " << war << "\tw_(x) = " << w_ << "\troznica = " << roznica << " <= " << ob << std::endl;
        xw += dx;
    }

    gsl_vector_free(a);
    gsl_vector_free(y);
    gsl_matrix_free(wsp);
    gsl_permutation_free(p);

    return 0;
}
