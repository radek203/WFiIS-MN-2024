#include <iostream>
#include "gsl/gsl_math.h"
#include "gsl/gsl_errno.h"
#include "gsl/gsl_fft_complex.h"

#define n (128)
#define pi (3.14159)

int main() {
    int i;
    double span = 6, t, y[2 * n];

    for (i = 0; i < n; i++) {
        t = (span / n) * i;
        y[2 * i] = 3.4 * sin(2 * pi * t) + 4.9 * sin(5 * pi * t) - 8.1 * sin(9 * pi * t); //czesc rzeczywista
        y[2 * i + 1] = 0.0; //czesc zespolona
    }

    gsl_fft_complex_radix2_forward(y, 1, n);

    for (i = 0; i < n; i++) {
        // moc zwiazana z i-ta czestotliwoscia
        printf("%.2f\n", i, sqrt(pow(y[2 * i], 2) + pow(y[2 * i + 1], 2)));
    }

    return 0;
}
