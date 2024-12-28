#include <stdio.h>
#include <iostream>
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
    gsl_vector *b = gsl_vector_calloc(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(fp, "%lf", &val);
            gsl_matrix_set(a, i, j, val);
        }
        fscanf(fp, "%lf", &val);
        gsl_vector_set(b, i, val);
    }

    fclose(fp);

    double x0[n], x1[n];
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

        x0[i] = 0;
        x1[i] = 0;
    }

    double norma = 0;
    do {
        norma = 0;
        for (int i = 0; i < n; i++) {
            x0[i] = x1[i];
        }
        for (int i = 0; i < n; i++) {
            double sum = 0;
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    sum += gsl_matrix_get(a, i, j) * x0[j];
                }
            }
            x1[i] = (gsl_vector_get(b, i) - sum) / gsl_matrix_get(a, i, i);

            norma += std::abs(x1[i] - x0[i]);
        }
    } while (norma > 0.0001);

    for (int i = 0; i < n; i++) {
        std::cout << x1[i] << std::endl;
    }


    return 0;
}
