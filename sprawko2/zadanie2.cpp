#include "../utils.h"

const std::string path = "A2.txt";

constexpr int n = 20;
constexpr int kmax = 500;
constexpr double eps = 0.0001;
constexpr double eps_spr = 0.001;
constexpr double omega = 1.0;

int main() {
    // Dla kazdego innego ukladu inna omega bedzie lepsza
    double a[n][n];
    double b[n];

    // Ladujemy macierz i wektor z pliku
    loadMatrixAndVectorFromFile(path, a, b);

    // Sprawdzamy czy ma dominujaca przekatna
    for (int i = 0; i < n; i++) {
        double sum = 0;

        for (int j = 0; j < n; j++) {
            if (i != j) {
                sum += std::abs(a[i][j]);
            }
        }

        if (sum >= std::abs(a[i][i])) {
            std::cout << "Nie ma dominujacej przekatnej!";
            return 1;
        }
    }

    // Obliczamy
    double x[n] = {};
    double x_copy[n];

    for (int k = 0; k < kmax; k++) {
        for (int i = 0; i < n; i++) {
            double sum = 0;
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    sum += a[i][j] * x[j];
                }
            }
            x_copy[i] = x[i];
            x[i] = (1 - omega) * x[i] + omega * (b[i] - sum) / a[i][i];
        }

        // Sprawdzamy osiagnieta dokladnosc
        double difference = 0;
        double reference = 0;
        for (int i = 0; i < n; i++) {
            difference += std::abs(pow(x[i] - x_copy[i], 2));
            reference += std::abs(pow(x_copy[i], 2));
        }

        if (sqrt(difference) < eps * sqrt(reference)) {
            std::cout << std::endl << "Osiagnelismy zadana dokladnosc po " << k << " iteracjach" << std::endl;
            break;
        }

        // Wypisujemy dane z co 5 iteracji
        if (k % 5 == 0) {
            std::cout << "Iteracja " << k << std::endl;
            printVector(x);
        }
    }

    // Wypisujemy wynik
    printVector(x);

    // Sprawdzamy wynik

    double check[n] = {};

    matrixVectorMultiply(a, x, check);

    std::cout << std::endl << "Sprawdzenie wyniku" << std::endl;
    printVector(check);

    bool isCorrect = true;
    for (int i = 0; i < n; i++) {
        if (std::abs(check[i] - b[i]) > eps_spr) {
            isCorrect = false;
            break;
        }
    }

    if (isCorrect) {
        std::cout << "Wynik jest poprawny" << std::endl;
    } else {
        std::cout << "Wynik jest niepoprawny" << std::endl;
    }

    return 0;
}
