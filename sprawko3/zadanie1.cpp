#include "../utils.h"

constexpr double eps = 1e-7;
constexpr double h = 1e-4;

double x_obl = 0.0;

double f_zad1_a1(double x) {
    return 2 * pow(x, 2) + (45.0 / 4.0) * pow(x, 6) - 2;
}

//Tutaj x jest naszym y
double f_zad1_a2(double x) {
    return -3 * pow(x_obl, 3) + 2 * x;
}

double f_zad1_b1(double x) {
    return cos(2 * pow(x, 3)) - 96 * pow(log(1 + pow(x, 2)), 5) + 1;
}

//Tutaj x jest naszym y
double f_zad1_b2(double x) {
    return 2 * log(1 + pow(x_obl, 2)) - x;
}

auto iloraz_roznicowy(double (*f)(double)) {
    return [f](double x) {
        return (f(x + h) - f(x - h)) / (2 * h);
    };
}

double bisection(double a, double b, double (*fun)(double)) {
    int i = 1;
    double x, y, ya;
    ya = fun(a);
    do {
        x = (a + b) / 2;
        //std::cout << "iteracja " << i << "   x = " << x << std::endl;
        y = fun(x);
        if (y == 0) break;
        if (ya * y > 0) {
            a = x;
            ya = y;
        } else {
            b = x;
        }
        i++;
    } while (0.5 * fabs(b - a) > eps);

    x = (a + b) / 2;

    return x;
}

double newton(double x, double (*fun)(double), const std::function<double(double)> &d_fun, int iter = 10) {
    for (int i = 1; i <= iter; i++) {
        x = x - fun(x) / d_fun(x);
        //std::cout << "iteracja " << i << "   x = " << x << " fun(x) = " << fun(x) << std::endl;
    }
    return x;
}

int main() {
    /* Zadanie 1 */
    std::cout << std::endl << "Zadanie 1a start" << std::endl;

    double result1_1_1 = bisection(0, 1.5, f_zad1_a1);
    x_obl = result1_1_1;
    double result1_1_2 = bisection(0, 1.5, f_zad1_a2);
    std::cout << "Zadanie 1a wynik (bisection) x = " << result1_1_1 << " y = " << result1_1_2 << std::endl;


    double result1_1_3 = newton(1.5, f_zad1_a1, iloraz_roznicowy(f_zad1_a1));
    x_obl = result1_1_3;
    double result1_1_4 = newton(1.5, f_zad1_a2, iloraz_roznicowy(f_zad1_a2));
    std::cout << "Zadanie 1a wynik (Newton) x = " << result1_1_3 << " y = " << result1_1_4 << std::endl;

    std::cout << std::endl << "Zadanie 1b start" << std::endl;

    double result1_2_1 = bisection(0, 1.5, f_zad1_b1);
    x_obl = result1_2_1;
    double result1_2_2 = bisection(0, 1.5, f_zad1_b2);
    std::cout << "Zadanie 1b wynik (bisection) x = " << result1_2_1 << " y = " << result1_2_2 << std::endl;


    double result1_2_3 = newton(1.5, f_zad1_b1, iloraz_roznicowy(f_zad1_b1));
    x_obl = result1_2_3;
    double result1_2_4 = newton(1.5, f_zad1_b2, iloraz_roznicowy(f_zad1_b2));
    std::cout << "Zadanie 1b wynik (Newton) x = " << result1_2_3 << " y = " << result1_2_4 << std::endl;


    return 0;
}
