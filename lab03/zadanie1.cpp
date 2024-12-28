#include <iostream>
#include <iomanip>

#define n 6

int main() {
    double c[n - 1] = {2, 3, -1, 1, 1};
    double d[n] = {1, 5, 7, 3, 2, 3};
    double d_copy[n] = {1, 5, 7, 3, 2, 3};
    double a[n - 1] = {-1, 2, 1, 4, -1};

    double x[n] = {};
    double b[n] = {1, 2, 3, 4, 5, 6};
    double b_copy[n] = {1, 2, 3, 4, 5, 6};

    for (int i = 1; i < n; i++) {
        d[i] = d[i] - c[i - 1] * (a[i - 1] / d[i - 1]);
        b[i] = b[i] - b[i - 1] * (a[i - 1] / d[i - 1]);
    }

    x[n - 1] = b[n - 1] / d[n - 1];

    for (int i = n - 2; i >= 0; i--) {
        x[i] = (b[i] - c[i] * x[i + 1]) / d[i];
    }

    for (int i = 0; i < n; i++) {
        std::cout << " x" << i << " = " << x[i] << std::endl;
    }

    //SPR
    for (int wiersz = 0; wiersz < n; wiersz++) {
        double sum = 0;
        if (wiersz > 0) {
            sum += a[wiersz - 1] * x[wiersz - 1];
        }
        sum += d_copy[wiersz] * x[wiersz];
        if (wiersz < n - 1) {
            sum += c[wiersz] * x[wiersz + 1];
        }
        std::cout << " sum: " << sum << " = " << b_copy[wiersz] << std::endl;
    }

    return 0;
}
