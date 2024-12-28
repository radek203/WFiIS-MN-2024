#include "../utilsGsl.h"

//O 1 mniej niz znamy punktow
constexpr int n = 8;

double fun(double x) {
    return sin(x);
}

int main() {
    gsl_vector *a = gsl_vector_calloc(n + 1);
    gsl_vector *y = gsl_vector_calloc(n + 1);

    gsl_matrix *wsp = gsl_matrix_calloc(n + 1, n + 1);

    double x[n + 1] = {0, M_PI / 4, M_PI / 2, M_PI * 3 / 4, M_PI, M_PI * 5 / 4, M_PI * 3 / 2, M_PI * 7 / 4, M_PI * 2};

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

    double xw = 0;
    double dx = 0.1;

    while (xw <= 2 * M_PI + dx) {
        double war = fun(xw);

        double w_ = 0;
        for (int i = 0; i < n + 1; i++) {
            w_ += gsl_vector_get(a, i) * pow(xw, i);
        }
        double roznica = std::abs(war - w_);

        double ob = 1;
        for (int i = 0; i < n + 1; i++) {
            ob *= (xw - x[i]);
        }
        // Dla tego przykladu ograniczenie od gory n+1 pochodna wyszedl cos(x) co daje max wartosc 1
        ob = std::abs(ob) / factorial(n + 1);

        std::cout << "x = " << xw << "\tf(x) = " << war << "\tw_(x) = " << w_ << "\troznica = " << roznica << " <= " << ob << std::endl;
        xw += dx;
    }

    gsl_vector_free(a);
    gsl_vector_free(y);
    gsl_matrix_free(wsp);
    gsl_permutation_free(p);

    return 0;
}
