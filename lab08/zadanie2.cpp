#include "../utils.h"

double h = pow(10, -6);

double f1(double x, double y) {
    return 2 * pow(x, 2) + 5 * pow(y, 2) - 2;
}

//Pochodna ilorazem roznicowym
double f1x_num(double x, double y) {
    return (f1(x + h, y) - f1(x - h, y)) / (2 * h);
}

double f1y_num(double x, double y) {
    return (f1(x, y + h) - f1(x, y - h)) / (2 * h);
}

double f2(double x, double y) {
    return -3 * pow(x, 3) + 2 * y - 0.1;
}

double f2x_num(double x, double y) {
    return (f2(x + h, y) - f2(x - h, y)) / (2 * h);
}

double f2y_num(double x, double y) {
    return (f2(x, y + h) - f2(x, y - h)) / (2 * h);
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

        double det = f1x_num(x, y) * f2y_num(x, y) - f2x_num(x, y) * f1y_num(x, y);
        //double DM1[2][2] = {{f2y(x, y) / det, f1x(x, y) / det}, {f2x(x, y) / det, f1x(x, y) / det}}

        // x_new = x - (DM^(-1) (x,y))*[f1(x,y), f2(x,y)]
        z[i][0] = x - (f2y_num(x, y) * f1(x, y) - f1y_num(x, y) * f2(x, y)) / det;
        z[i][1] = y - (-f2x_num(x, y) * f1(x, y) + f1x_num(x, y) * f2(x, y)) / det;
    }

    std::cout << std::setprecision(10);
    std::cout << "Wynik: x = " << z[99][0] << " y = " << z[99][1] << " f1(x,y) = " << f1(x, y) << " f2(x,y) = " << f2(x, y) << std::endl;

    return 0;
}
