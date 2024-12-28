#include <stdio.h>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <gsl/gsl_linalg.h>

int main() {
    int n = 5;

    FILE *fp;
    if ((fp = fopen("daneJac.txt", "rt")) == NULL) {
        printf("\n*** (daneJac.txt) ***\n");
        return 1;
    }

    double val;

    gsl_matrix *a = gsl_matrix_calloc(n, n);
    gsl_matrix *a_prime = gsl_matrix_calloc(n, n);
    gsl_vector *b = gsl_vector_calloc(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(fp, "%lf", &val);
            gsl_matrix_set(a, i, j, val);
            gsl_matrix_set(a_prime, i, j, 0);
        }
        fscanf(fp, "%lf", &val);
        gsl_vector_set(b, i, val);
    }

    fclose(fp);

    double x[n];
    for (int i = 0; i < n; i++) {
        double sum = 0;

        for (int j = 0; j < n; j++) {
            if (i != j) {
                sum += std::abs(gsl_matrix_get(a, i, j));
            }
        }

        if (sum >= gsl_matrix_get(a, i, i)) {
            std::cout << "Nie ma dominujacej przekatnej!";
            return 1;
        }

        x[i] = 0;
    }

    // Dodatkowymi krokami mozna obliczyc macierz odwrotna
    for (int col = 0; col < n; col++) {
        for (int w = 0; w < n; w++) {
            gsl_vector_set(b, w, col == w ? 1 : 0);
        }
        for (int k = 0; k < 100; k++) {
            for (int i = 0; i < n; i++) {
                double sum = 0;
                for (int j = 0; j < n; j++) {
                    if (i != j) {
                        sum += gsl_matrix_get(a, i, j) * x[j];
                    }
                }
                x[i] = (gsl_vector_get(b, i) - sum) / gsl_matrix_get(a, i, i);
            }
        }
        for (int w = 0; w < n; w++) {
            gsl_matrix_set(a_prime, w, col, x[w]);
        }
    }

    double c[5][5] = {};
    for (int wiersz1 = 0; wiersz1 < n; wiersz1++) {
        for (int kolumna2 = 0; kolumna2 < n; kolumna2++) {
            for (int kolumna1 = 0; kolumna1 < n; kolumna1++) {
                c[wiersz1][kolumna2] += gsl_matrix_get(a, wiersz1, kolumna1) * gsl_matrix_get(a_prime, kolumna1, kolumna2);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << c[i][j] << " ";
        }
        std::cout << std::endl;
    }


    return 0;
}
