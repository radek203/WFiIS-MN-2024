#include <iostream>
#include <cmath>
#include <iomanip>
#define eps 1e-8
#define e exp(1.0)
using namespace std;

//Znalezc maksimium rozkladu Plancka (pochodna = 0)
//Pochodna = 3(e^x - 1)- xe^x = 0

//Jak zaczniemy w x = 1, nigdy nie znajdzie
//Jak zaczniemy w x = 2, x = -inf, fun(x) = nan, wywala sie
//Jak zaczniemy w x wiekszym od naszego miejsca zerowego to zadziala
double fun(double x) {
    //3(e^x -1) - xe^x = 0
    return 3 * (pow(e, x) - 1) - x * pow(e, x);
}

//Tej funkcji nie umie zrobic, jezeli nie wprowadzimy eps
double fun2(double x) {
    //(3-x)e^x - 3 = 0
    return (3 - x) * pow(e, x) - 3;
}

//Jak zacznimy w x = 3, nie umie znalezc
//Jak zaczniemy w x = 2.9, to dziala po zastosowaniu eps
double fun3(double x) {
    //e^x - 3/(3-x) = 0
    return pow(e, x) - 3 / (3 - x);
}

double d_fun(double x) {
    //3e^x - (e^x + xe^x)
    //2e^x - xe^x
    return 2 * pow(e, x) - x * pow(e, x);
}

double d_fun2(double x) {
    //e^x(2-x)
    return pow(e, x) * (2 - x);
}

double d_fun3(double x) {
    //e^x - 3/(3-x) = 0
    //e^x - 3/(3-x)^2
    return pow(e, x) - 3 / pow(3 - x, 2);
}

void newton() {
    //Metoda Newtona

    double result = 0;
    double x = 2.86;
    for (int i = 0; i < 15; i++) {
        x = x - fun3(x) / d_fun3(x);
        result = fun3(x);
        cout << "x = " << x << " fun(x) = " << result << endl;
        /*
        if (abs(fun(x)) < eps) {
            cout << " mniejsze od eps ";
            break;
        }
        */
        if (abs(result) == 0) {
            break;
        }
    }
}

//Dziala zawsze
void bisection() {
    //Metoda bisekcji
    double a = 0.1;
    double b = 3;

    double x = 0;
    while (abs(a - b) > eps) {
        cout << "Zmienia znak na przedziale... (" << a << ", " << b << ")" << endl;
        x = (a + b) / 2.0;
        if (fun3(x) * fun3(a) < eps) {
            b = x;
        } else {
            a = x;
        }
    }
    cout << "Miejsce zerowe: " << (a + b) / 2.0 << endl;
}

int main() {
    cout << "Newton method:" << endl << std::setprecision(15);

    newton();

    cout << endl << "Bisection method:" << endl;

    bisection();

    return 0;
}
