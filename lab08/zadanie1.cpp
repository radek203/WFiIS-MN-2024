#include <iostream>
#include <cmath>
#include <iomanip>

double f1(double x, double y) {
    return pow(x, 4) + pow(y, 2) - 2 * x + 4 * y - 3;
}

double f1x(double x, double y) {
    return 4 * pow(x, 3) - 2;
}

double f1y(double x, double y) {
    return 2 * y + 4;
}

double f2(double x, double y) {
    return 9 * pow(x, 2) + 4 * pow(y, 2) + 16 * y - 20;
}

double f2x(double x, double y) {
    return 18 * x;
}

double f2y(double x, double y) {
    return 8 * y + 16;
}


int main() {
    double x;
    double y;

    double z[100][2] = {};
    z[0][0] = 1.5; //0.5;
    z[0][1] = 0; //1;

    for (int i = 1; i < 100; i++) {
        x = z[i - 1][0];
        y = z[i - 1][1];

        double det = f1x(x, y) * f2y(x, y) - f2x(x, y) * f1y(x, y);
        //double DM1[2][2] = {{f2y(x, y) / det, f1x(x, y) / det}, {f2x(x, y) / det, f1x(x, y) / det}}

        // x_new = x - (DM^(-1) (x,y))*[f1(x,y), f2(x,y)]
        z[i][0] = x - (f2y(x, y) * f1(x, y) - f1y(x, y) * f2(x, y)) / det;
        z[i][1] = y - (-f2x(x, y) * f1(x, y) + f1x(x, y) * f2(x, y)) / det;
    }

    std::cout << std::setprecision(10);
    std::cout << "Wynik: x = " << z[99][0] << " y = " << z[99][1] << " f1(x,y) = " << f1(x, y) << " f2(x,y) = " << f2(x, y) << std::endl;

    return 0;
}
