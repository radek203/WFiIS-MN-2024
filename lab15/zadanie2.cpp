#include "../utilsGsl.h"

double fun(double x) {
    return pow(x, 4) * sin(x);
}

int main() {
    double start = -2;
    double end = 2;

    double suma = 0;

    double steps = 1000.0;
    double step = (end - start) / steps;
    for (double i = start; i < end; i += step) {
        double a = i;
        double b = i + step;

        double P = (b - a) * (fun(a) + fun(b)) / 2.0;
        suma += P;
    }

    std::cout << "Pole: " << suma << std::endl;


    return 0;
}
