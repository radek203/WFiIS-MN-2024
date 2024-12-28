#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double fun(double x) {
    return x * x * x + sin(x) + 1;
}

double d_fun(double x) {
    return 3 * x * x + cos(x);
}

int main() {
    std::cout << std::setprecision(15);
    //Metoda Newtona

    double result = 0;
    double x = -1;
    for (int i = 0; i < 15; i++) {
        x = x - fun(x) / d_fun(x);
        result = fun(x);
        cout << "x = " << x << " fun(x) = " << result;
        /*
        if (abs(fun(x)) < 1e-6) {
            cout << " mniejsze od eps ";
        }
        */
        cout << endl;
        if (result == 0) {
            break;
        }
    }

    return 0;
}
