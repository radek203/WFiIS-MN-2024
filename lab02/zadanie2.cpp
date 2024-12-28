#include <iostream>
#include <cmath>
#include <iomanip>
#define eps 1e-8

using namespace std;

double fun(double x) {
    return x * x * x * x * x + x + 1;
}

int main() {
    std::cout << std::setprecision(15);
    //Metoda bisekcji
    double a = -2;
    double b = 0;

    double x = 0;
    while (abs(a - b) > eps) {
        cout << "Zmienia znak na przedziale... (" << a << ", " << b << ")" << endl;
        x = (a + b) / 2.0;
        if (fun(x) * fun(a) < eps) {
            b = x;
        } else {
            a = x;
        }
    }
    cout << "Miejsce zerowe: " << (a + b) / 2.0 << endl;

    return 0;
}
