#include <iostream>
#include <ostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#define eps 1e-8
#define e exp(1.0)
using namespace std;

int main() {
    double c = 100;
    int n = 3;
    double x[20] = {};
    x[0] = c > 1 ? c : 1;
    for (int i = 1; i < 20; i++) {
        //x[i] = 0.5 * (x[i-1] + c / (x[i-1]));
        x[i] = (1.0 / n) * ((n - 1) * x[i - 1] + c / pow(x[i - 1], n - 1));
        cout << "x[" << i << "] = " << x[i] << endl;
    }

    cout << "Wynik: " << x[19] << endl;

    return 0;
}
