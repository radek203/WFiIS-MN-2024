#include <iostream>
#include <ostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#define eps 1e-8
#define e exp(1.0)
#define K_A (2.5*pow(10, -5))
#define K_W (pow(10, -14))
using namespace std;

double f_zad2_a(double x) {
    return pow(x, 3) - 4 * x + 1;
}

double f_zad2_b(double x) {
    return x - 3 * sin(x) - 1;
}

double f_zad2_c(double x) {
    return x * log(x) + sin(x);
}

double f_zad2_d(double x) {
    return pow(e, -3 * x) + pow(x, 5) - 3 * pow(x, 2) + 1;
}

double f_zad3_a(double x) {
    return pow(x, 5) + 3 * pow(x, 3) + 2;
}

double Df_zad3_a(double x) {
    return 5 * pow(x, 4) + 9 * pow(x, 2);
}

double f_zad3_b(double x) {
    return pow(e, x) - pow(x, 2) - 1;
}

double Df_zad3_b(double x) {
    return pow(e, x) - 2 * x;
}

double f_zad3_c(double x) {
    return (x / (pow(x, 2) + 1)) - atan(x);
}

double Df_zad3_c(double x) {
    return -((2 * pow(x, 2)) / (pow(x, 4) + 2 * pow(x, 2) + 1));
}

double f_zad3_d(double x) {
    return sin(sin(x));
}

double Df_zad3_d(double x) {
    return cos(x) * cos(sin(x));
}

double bisection(double a, double b, double (*fun)(double)) {
    int i = 1;
    double x, y, ya;
    ya = fun(a);
    do {
        x = (a + b) / 2;
        cout << "iteracja " << i << "   x = " << x << endl;
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

double falsi(double a, double b, double (*fun)(double)) {
    double c = a;

    while (fabs(fun(b) - fun(a)) > eps) {
        c = (a * fun(b) - b * fun(a)) / (fun(b) - fun(a));

        if (fabs(fun(c)) <= eps) {
            break;
        }

        if (fun(c) * fun(a) < 0) {
            b = c;
        } else {
            a = c;
        }
    }

    return c;
}

double newton(double x, double (*fun)(double), double (*d_fun)(double), int iter = 10) {
    for (int i = 1; i <= iter; i++) {
        x = x - fun(x) / d_fun(x);
        cout << "iteracja " << i << "   x = " << x << " fun(x) = " << fun(x) << endl;
    }
    return x;
}

double newton_pierwiastek(double c, int n, int iterNum) {
    double x = c / n;

    for (int i = 0; i < iterNum; i++) {
        //x[i] = 0.5 * (x[i-1] + c / (x[i-1]));
        x = (1.0 / n) * ((n - 1) * x + c / pow(x, n - 1));
    }

    return x;
}

double f_zad3(double x, double c0) {
    return pow(x, 3) + K_A * pow(x, 2) - (K_W + c0 * K_A) * x - K_A * K_W;
}

double bisection(double a, double b, double c) {
    int i = 1;
    double x, y, ya;
    ya = f_zad3(a, c);
    do {
        x = (a + b) / 2;
        //cout << "iteracja " << i << "   x = " << x << endl;
        y = f_zad3(x, c);
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

double f_zad1_1(double x) {
    return (tan(x) / x) + 1;
}

double Df_zad1_1(double x) {
    return (x / pow(cos(x), 2) - tan(x)) / pow(x, 2);
}

double f_zad1_2(double x) {
    return pow(x, 2) - log(x) - 4;
}

double Df_zad1_2(double x) {
    return 2 * x - (1 / x);
}

int main() {
    /* Zadanie 1 */
    cout << "Zadanie 1 start" << endl;

    double result1_1_1 = bisection(1.75, 2.25, f_zad1_1);
    double result1_1_2 = newton(2.25, f_zad1_1, Df_zad1_1);
    cout << "Zadanie 1 wynik 1 x = " << result1_1_1 << " x = " << result1_1_2 << endl;

    double result1_2_1 = bisection(1.5, 3, f_zad1_2);
    double result1_2_2 = newton(3, f_zad1_2, Df_zad1_2);
    cout << "Zadanie 1 wynik 2 x = " << result1_2_1 << " x = " << result1_2_2 << endl;

    /* Zadanie 2, pudpunkt a */
    cout << "Zadanie 2a start" << endl;
    double result2a = bisection(0, 1, f_zad2_a);
    cout << "Zadanie 2a wynik x = " << result2a << endl;

    /* Zadanie 2, pudpunkt b */
    cout << "Zadanie 2b start" << endl;
    double result2b = bisection(2, 3, f_zad2_b);
    cout << "Zadanie 2b wynik x = " << result2b << endl;

    /* Zadanie 2, pudpunkt c */
    cout << "Zadanie 2c start" << endl;
    double result2c = bisection(0.2, 0.5, f_zad2_c);
    cout << "Zadanie 2c wynik x = " << result2c << endl;

    /* Zadanie 2, pudpunkt d */
    cout << "Zadanie 2d start" << endl;
    double result2d = bisection(0, 1, f_zad2_d);
    cout << "Zadanie 2d wynik x = " << result2d << endl;

    /* Zadanie 3, pudpunkt a */
    cout << "Zadanie 3a start" << endl;
    double result3a = newton(-0.5, f_zad3_a, Df_zad3_a);
    cout << "Zadanie 3a wynik x = " << result3a << endl;

    /* Zadanie 3, pudpunkt b */
    cout << "Zadanie 3b start" << endl;
    double result3b = newton(1, f_zad3_b, Df_zad3_b);
    cout << "Zadanie 3b wynik x = " << result3b << endl;

    /* Zadanie 3, pudpunkt c */
    cout << "Zadanie 3c start" << endl;
    double result3c = newton(0.5, f_zad3_c, Df_zad3_c, 30);
    cout << "Zadanie 3c wynik x = " << result3c << endl;

    /* Zadanie 3, pudpunkt d */
    cout << "Zadanie 3d start" << endl;
    double result3d = newton(0.5, f_zad3_d, Df_zad3_d);
    cout << "Zadanie 3d wynik x = " << result3d << endl;

    /* Zadanie 4 */
    cout << "Zadanie 4 start" << endl;
    double c = 21.0;
    int n = 3;
    int iterNum = 10;

    double root = newton_pierwiastek(c, n, iterNum);
    cout << "Pierwiastek " << n << "-tego stopnia z " << c << " wynosi " << root << endl;

    /* Zadanie 5 */
    cout << "Zadanie 5 start" << endl;
    double c0 = pow(10, -9);
    ofstream file;
    file.open("plik.txt");
    while (c0 <= 1) {
        double c0_value = log10(c0);
        double result = -log10(bisection(0, 1, c0));
        cout << " c0: " << c0_value << " x0 = " << result << endl;
        file << c0_value << " " << result << "\n";
        c0 *= pow(10, 1.0 / 6);
    }
    file.close();

    return 0;
}
