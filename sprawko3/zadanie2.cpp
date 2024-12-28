#include "../utils.h"

// 2x - sin(0.5x + y) = 0
double f_zad2_a1(double x, double y) {
    return 0.5 * sin(0.5 * x + y);
}

// y - 0.5 cos(x - 0.5y) = 0
double f_zad2_a2(double x, double y) {
    return 0.5 * cos(x - 0.5 * y);
}

// x + x / (1 + x^2) - 1/3 sin(y) = 0
double f_zad2_b1(double x, double y) {
    return -x / (1 + pow(x, 2)) + sin(y) / 3;
}

// 0.4 cos(x) + y / (3 + y^2) - 2y = 0
double f_zad2_b2(double x, double y) {
    return 0.2 * cos(x) + y / (2 * (3 + pow(y, 2)));
}

void iteracji_prostych(double fun1(double, double), double fun2(double, double), int iteracji = 20, double x = 0, double y = 0) {
    double xcopy = x;
    double ycopy = y;
    for (int i = 0; i < iteracji; i++) {
        x = fun1(xcopy, ycopy);
        y = fun2(xcopy, ycopy);
        xcopy = x;
        ycopy = y;
    }

    printValue("x", x);
    printValue("y", y);
    printValue("fun1(x,y)", fun1(x, y));
    printValue("fun2(x,y)", fun2(x, y));
}

int main() {
    /* Zadanie 2 */
    std::cout << std::endl << "Zadanie 2a start" << std::endl;
    iteracji_prostych(f_zad2_a1, f_zad2_a2, 20);

    std::cout << std::endl << "Zadanie 2b start" << std::endl;
    iteracji_prostych(f_zad2_b1, f_zad2_b2, 1000);


    return 0;
}
