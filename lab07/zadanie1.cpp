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

    for (int i = 0; i < n; i++) {
        std::cout << x[i] << std::endl;
    }


    return 0;
}
