#include <iostream>
#include <fstream>
#define n 5

void printMatrix(int matrix[n][n]) {
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            std::cout << " " << matrix[x][y];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    std::ifstream fileA;
    fileA.open("A.txt");

    std::ifstream fileB;
    fileB.open("B.txt");

    int a[5][5], b[5][5], c[5][5] = {};
    for (int i = 0; i < n * n; i++) {
        fileA >> a[i / 5][i % 5];
    }
    for (int i = 0; i < n * n; i++) {
        fileB >> b[i / 5][i % 5];
    }
    printMatrix(a);
    printMatrix(b);

    for (int wiersz1 = 0; wiersz1 < n; wiersz1++) {
        for (int kolumna2 = 0; kolumna2 < n; kolumna2++) {
            for (int kolumna1 = 0; kolumna1 < n; kolumna1++) {
                c[wiersz1][kolumna2] += a[wiersz1][kolumna1] * b[kolumna1][kolumna2];
            }
        }
    }

    printMatrix(c);

    std::ofstream fileC;
    fileC.open("C.txt");
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            fileC << c[x][y] << " ";
        }
        fileC << "\n";
    }

    return 0;
}
