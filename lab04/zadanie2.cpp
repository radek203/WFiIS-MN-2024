#include <iostream>
#include <ostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#define eps 1e-8
#define e exp(1.0)
using namespace std;

int main() {
    std::ifstream fileA;
    fileA.open("Ab.txt");

    double tempValue;
    int n = 0;
    char checkForNewLine;

    while (fileA >> tempValue) {
        ++n;
        if ((checkForNewLine = fileA.peek()) == '\n' || checkForNewLine == EOF) {
            break;
        }
    }
    n = n - 1;
    fileA.seekg(0, ios::beg);

    double A[n][n], b[n];
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            fileA >> A[x][y];
        }
        fileA >> b[x];
    }

    printf("\nMacierz A:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%f ", A[i][j]);
        }
        printf("\n");
    }

    printf("\nVector b:\n");
    for (int i = 0; i < n; i++) {
        printf("%f\n", b[i]);
    }

    int p[n];
    for (int i = 0; i < n; i++) {
        p[i] = i;
    }

    for (int i = 0; i < n; i++) {
        //Wybor elementu glownego
        int max_index = i;
        for (int j = i + 1; j < n; j++) {
            if (fabs(A[p[max_index]][i]) < fabs(A[p[j]][i])) {
                max_index = j;
            }
        }

        //Zamiana wierszy (wektor permutacji)
        if (max_index > i) {
            int temp = p[i];
            p[i] = p[max_index];
            p[max_index] = temp;
        }

        //Sprowadzamy do macierzy trojkatnej gornej
        for (int j = i + 1; j < n; j++) {
            double wsp = A[p[j]][i] / A[p[i]][i];

            for (int k = i; k < n; k++) {
                A[p[j]][k] = A[p[j]][k] - (A[p[i]][k] * wsp);
            }

            b[p[j]] = b[p[j]] - (b[p[i]] * wsp);
        }
    }

    //Rozwiazujemy
    for (int i = n - 1; i >= 0; i--) {
        b[p[i]] = b[p[i]] / A[p[i]][i];

        for (int j = i - 1; j >= 0; j--) {
            b[p[j]] = b[p[j]] - (A[p[j]][i] * b[p[i]]);
        }
    }

    printf("\nRozwiazania:\n");

    for (int i = 0; i < n; i++) {
        printf("%f\n", b[p[i]]);
    }

    return 0;
}
