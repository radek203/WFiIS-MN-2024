#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>

int main(void) {
    int i, n = 10;
    double xi, yi, x[n], y[n];

    printf("\n*** Dane: węzły interpolacji ***\n");
    for (i = 0; i < n; i++) {
        x[i] = i + 1.0 / (i + 1);
        y[i] = (2 + 3 * x[i] - 0.5 * x[i] * x[i] + 1.5 * pow(x[i], 4)) * exp(-x[i]) + 3 * sin(x[i]);
        printf("%g %g\n", x[i], y[i]);
    }

    // Znajdowanie zwykłego wielomianu interpolacyjnego (ściśle - to nie jest splajn)
    gsl_spline *spline = gsl_spline_alloc(gsl_interp_polynomial, n);
    gsl_interp_accel *acc = gsl_interp_accel_alloc();
    gsl_spline_init(spline, x, y, n);

    printf("\n*** Wyniki: wartości wielomianu interpolacyjnego w wybranych punktach ***\n");
    for (xi = x[0]; xi < x[n - 1]; xi += 0.1) {
        yi = gsl_spline_eval(spline, xi, acc);
        printf("%g %g\n", xi, yi);
    }

    gsl_spline_free(spline);
    gsl_interp_accel_free(acc);

    return 0;
}
