#include <iostream>
#include <ostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#define eps 1e-8
#define e exp(1.0)
using namespace std;

int main() {
    int n = 6, m = 6;

    double A[n][m] = {{2, 4, 1, 2, 5, 6}, {1, -1, 3, 5, 3, 7}, {6, 4, 1, 2, 1, 7}, {9, 3, 2, 3, 5, 9}, {5, 4, 2, 2, -2, 7}, {4, 5, 2, -1, 2, 5}};
    double b[n] = {1, 2, 3, 4, 5, 6};

    printf("\nMacierz A:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%f ", A[i][j]);
        }
        printf("\n");
    }

    printf("\nVector b:\n");
    for (int i = 0; i < n; i++) {
        printf("%f\n", b[i]);
    }

    for (int i = 0; i < n; i++) {
        //Wybor elementu glownego
        int max_index = i;
        for (int j = i + 1; j < n; j++) {
            if (fabs(A[max_index][i]) < fabs(A[j][i])) {
                max_index = j;
            }
        }

        //Zamiana wierszy
        if (max_index > i) {
            for (int k = i; k < n; k++) {
                double copy = A[i][k];
                A[i][k] = A[max_index][k];
                A[max_index][k] = copy;
            }

            double copy_b = b[i];
            b[i] = b[max_index];
            b[max_index] = copy_b;
        }

        //Sprowadzamy do macierzy trojkatnej gornej
        for (int j = i + 1; j < n; j++) {
            double wsp = A[j][i] / A[i][i];

            for (int k = i; k < n; k++) {
                A[j][k] = A[j][k] - (A[i][k] * wsp);
            }

            b[j] = b[j] - (b[i] * wsp);
        }
    }

    //Rozwiazujemy
    for (int i = n - 1; i >= 0; i--) {
        b[i] = b[i] / A[i][i];

        for (int j = i - 1; j >= 0; j--) {
            b[j] = b[j] - (A[j][i] * b[i]);
        }
    }

    printf("\nRozwiazania:\n");

    for (int i = 0; i < n; i++) {
        printf("%f\n", b[i]);
    }

    return 0;
}
