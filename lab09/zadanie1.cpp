#include "../utils.h"

double f(double x) {
    return (pow(x, 2) + 1) / (pow(x, 4) + 2 + sin(x));
}

// x - 0.5cos(x) + 0.1 y^2 = 0
double f1(double x, double y) {
    return -0.5 * cos(x) + 0.1 * pow(y, 2);
}

// y - 0.34sin(x) + 0.5 y^4 = 0
double f2(double x, double y) {
    return 0.34 * sin(x) + 0.5 * pow(y, 4);
}

// 2x - sin(0.5x + y) = 0
double f3(double x, double y) {
    return 0.5 * sin(0.5 * x + y);
}

// y - 0.5 cos(x - 0.5y) = 0
double f4(double x, double y) {
    return 0.5 * cos(x - 0.5 * y);
}

// x + x / (1 + x^2) - 1/3 sin(y) = 0
double f5(double x, double y) {
    return -x / (1 + pow(x, 2)) + sin(y) / 3;
}

// 0.4 cos(x) + y / (3 + y^2) - 2y = 0
double f6(double x, double y) {
    return 0.2 * cos(x) + y / (2 * (3 + pow(y, 2)));
}

void oblicz(double fun1(double, double), double fun2(double, double), int iteracji = 20, double x = 0, double y = 0) {
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
    // Metoda prostych iteracji
    double x = 1;
    for (int i = 0; i < 20; i++) {
        x = f(x);
    }

    printValue("x", x);
    printValue("f(x)", f(x));


    std::cout << std::endl << "Dla f1 i f2" << std::endl;
    oblicz(f1, f2, 20);
    //oblicz([](double x, double y) { return - 0.5 * cos(x) + 0.1 * pow(y, 2);}, [](double x, double y) { return 0.34 * sin(x) + 0.5 * pow(y, 4);});

    std::cout << std::endl << "Dla f3 i f4" << std::endl;
    oblicz(f3, f4, 20);

    std::cout << std::endl << "Dla f5 i f6" << std::endl;
    oblicz(f5, f6, 1000);
}
